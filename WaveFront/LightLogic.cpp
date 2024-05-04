#include "LightLogic.h"


CoordinateStruct calculatePhongLight(CoordinateStruct& Point, CoordinateStruct& hitNormal, CoordinateStruct& cameraPosition, std::vector<PointLightStruct> lightnings)
{
	CoordinateStruct hitColor, diffuseLightFinalColor, specularLightFinalColor;

	CoordinateStruct diffuse = { 0,0,0 }, specular = { 0,0,0 };

	for (auto i = 0; i < lightnings.size(); ++i) {

		CoordinateStruct lightDirection, lightIntensity;

		// ambient light intensity
		lightnings[i].illuminate(Point, lightDirection, lightIntensity);

		// compute diffuse 
		diffuse = diffuse + (lightIntensity * getMax(0.f, DotProduct(hitNormal, ReverseVector(lightDirection))) * lightnings[i].objectAlbedo);

		// compute the specular component
		// what would be the ideal reflection direction for this light ray
		CoordinateStruct reflectionDirection = GetReflectionDirection(lightDirection, hitNormal);

		CoordinateStruct cameraDirection = Normalize(SubstractVectors(cameraPosition, Point));
		specular = specular + (lightIntensity * std::pow(getMax(0.f, DotProduct(reflectionDirection, cameraDirection)), lightnings[i].PhongSpecularExponent));

		// end for 
		diffuseLightFinalColor = (diffuse * lightnings[i].PhongDiffuseWeight);
		specularLightFinalColor = (specular * lightnings[i].PhongSpecularWeight);
	}
	hitColor = (diffuseLightFinalColor + specularLightFinalColor);
	return hitColor;
}



CoordinateStruct calculatePhongLight(CoordinateStruct& Point, CoordinateStruct& hitNormal, CoordinateStruct& cameraPosition, std::vector<PointLightStruct> lightnings, float specularWeight)
{
	float diffuseWeight = 1 - specularWeight;

	CoordinateStruct hitColor, diffuseLightFinalColor, specularLightFinalColor;

	CoordinateStruct diffuse = { 0,0,0 }, specular = { 0,0,0 };

	for (auto i = 0; i < lightnings.size(); ++i) {

		CoordinateStruct lightDirection, lightIntensity;

		// ambient light intensity
		lightnings[i].illuminate(Point, lightDirection, lightIntensity);

		// compute diffuse 
		diffuse = diffuse + (lightIntensity * getMax(0.f, DotProduct(hitNormal, ReverseVector(lightDirection))) * lightnings[i].objectAlbedo);

		// compute the specular component
		// what would be the ideal reflection direction for this light ray
		CoordinateStruct reflectionDirection = GetReflectionDirection(lightDirection, hitNormal);

		CoordinateStruct cameraDirection = Normalize(SubstractVectors(cameraPosition, Point));
		specular = specular + (lightIntensity * std::pow(getMax(0.f, DotProduct(reflectionDirection, cameraDirection)), lightnings[i].PhongSpecularExponent));

		// end for 
		diffuseLightFinalColor = (diffuse * diffuseWeight);
		specularLightFinalColor = (specular * specularWeight);
	}
	hitColor = (diffuseLightFinalColor + specularLightFinalColor);
	return hitColor;
}

CoordinateStruct GetReflectionDirection(const CoordinateStruct& lightDirection, const CoordinateStruct& hitNormal)
{
	CoordinateStruct result;
	result = lightDirection - hitNormal * (2 * DotProduct(lightDirection, hitNormal));
	return result;
}

CoordinateStruct fresnelSchlick(float cosTheta, CoordinateStruct F0) // F0 поверхностное отражение при нулевом падении
{
	CoordinateStruct identVec = { 1,1,1 };
	CoordinateStruct tempSub = { 1.0 - F0.x,1.0 - F0.y,1.0 - F0.z };
	return F0 + (identVec - F0) * std::pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}

float DistributionGGX(CoordinateStruct& Normal, CoordinateStruct& Halfway, float roughness)
{
	float a = roughness * roughness;
	float a2 = a * a;
	float NdotH = getMax(DotProduct(Normal, Halfway), 0.f);
	float NdotH2 = NdotH * NdotH;

	float num = a2;
	float denom = (NdotH2 * (a2 - 1.0) + 1.0);
	denom = M_PI * denom * denom;

	return num / denom;
}

float GeometrySchlickGGX(float NdotV, float roughness)
{
	float r = (roughness + 1.0);
	float k = (r * r) / 8.0f	;

	float num = NdotV;
	float denom = NdotV * (1.0 - k) + k;

	return num / denom;
}

float GeometrySmith(CoordinateStruct& N, CoordinateStruct& V, CoordinateStruct& L, float roughness)
{
	float NdotV = getMax(DotProduct(N, V), 0.0f);
	float NdotL = getMax(DotProduct(N, L), 0.0f);
	float ggx2 = GeometrySchlickGGX(NdotV, roughness);
	float ggx1 = GeometrySchlickGGX(NdotL, roughness);

	return ggx1 * ggx2;
}

CoordinateStruct calculatePBRLight(CoordinateStruct& Point, CoordinateStruct& hitNormal, CoordinateStruct& cameraPosition, std::vector<PointLightStruct> lightnings,
	CoordinateStruct& albedo, float metallic, float roughness, float ambientOcclusion, CoordinateStruct& material)
{
	CoordinateStruct identVec = { 1,1,1 };
	int i = 0;

	CoordinateStruct cameraDirection = Normalize(SubstractVectors(cameraPosition, Point));

	//Average F0 for dielectric materials
	//CoordinateStruct F0 = { 0.04f,0.04f,0.04f };
	CoordinateStruct F0 = material;
	CoordinateStruct albedoVec = Normalize(albedo);
	F0 = getMix(F0, albedoVec, metallic); // Linear

	CoordinateStruct Lo = { 0.f,0.f,0.f };

	for (auto i = 0; i < lightnings.size(); ++i) {

		// Calculate per-light radiance
		CoordinateStruct lightDirection = Normalize(SubstractVectors(lightnings[i].globalPosition, Point));
		CoordinateStruct halfwayVector = Normalize(cameraDirection + lightDirection);

		float lightDistance = GetVectorLength(SubstractVectors(lightnings[i].globalPosition, Point));
		float attentuation = 1.0 / (lightDistance * lightDistance);
		CoordinateStruct lightColorWithIntensity = lightnings[i].LightColor * lightnings[i].LightIntesity ;
		CoordinateStruct radiance = lightColorWithIntensity * attentuation;
		//CoordinateStruct radiance = lightnings[i].LightColor * attentuation;

		//////
		// cook-torrance brdf
		float NDF = DistributionGGX(hitNormal, halfwayVector, roughness);
		float G = GeometrySmith(hitNormal, cameraDirection, lightDirection, roughness);
		CoordinateStruct F = fresnelSchlick(getMax(DotProduct(halfwayVector, cameraDirection), 0.0f), F0);

		CoordinateStruct kS = F;
		CoordinateStruct kD = identVec - kS;
		kD = kD * (1.0 - metallic);

		CoordinateStruct numerator = F * NDF * G;
		float denominator = 4.0 * getMax(DotProduct(hitNormal, cameraDirection), 0.0f) * getMax(DotProduct(hitNormal, lightDirection), 0.0f) + 0.0001;
		CoordinateStruct specular = numerator / denominator;

		// add to outgoing radiance Lo
		float NdotL = getMax(DotProduct(hitNormal, lightDirection), 0.0f);
		CoordinateStruct temp1 = (kD * albedoVec / M_PI + specular);
		CoordinateStruct temp2 = radiance * NdotL;
		CoordinateStruct res = temp1 * temp2;
		Lo = Lo + res;
	}
	CoordinateStruct tempAmbCoef = { 0.03f,0.03f,0.03f };
	CoordinateStruct ambient = tempAmbCoef * albedoVec * ambientOcclusion;
	CoordinateStruct color = ambient + Lo;

	color.x = color.x / (color.x + 1);
	color.y = color.y / (color.y + 1);
	color.z = color.z / (color.z + 1);

	color.x = pow(color.x, 1.0 / 2.2);
	color.y = pow(color.y, 1.0 / 2.2);
	color.z = pow(color.z, 1.0 / 2.2);


	return color;
}
