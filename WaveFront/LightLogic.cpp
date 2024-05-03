#include "LightLogic.h"


CoordinateStruct calculatePhongLight(CoordinateStruct& Point, CoordinateStruct& hitNormal, CoordinateStruct& cameraPosition, std::vector<PointLightStruct> lightnings)
{
	CoordinateStruct hitColor, diffuseLightFinalColor, specularLightFinalColor;

	CoordinateStruct diffuse = {0,0,0}, specular = { 0,0,0 };

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

CoordinateStruct calculatePBRLight(CoordinateStruct& Point, CoordinateStruct& hitNormal, CoordinateStruct& cameraPosition, std::vector<PointLightStruct> lightnings, 
	float albedo, float metallic, float roughness, float ambientOcclusion)
{
	int i = 0;

	CoordinateStruct wi = Normalize(SubstractVectors(lightnings[i].globalPosition, Point));
	float cosTheta = getMax(DotProduct(hitNormal, wi), 0.0f); // ????
	//float attentuation = calculateAtentuation(Point, lightnings[i].globalPosition);
	//CoordinateStruct radiance = lightColor * attenuation * cosTheta;

	CoordinateStruct cameraDirection = Normalize(SubstractVectors(cameraPosition, Point));
	CoordinateStruct lightDirection = Normalize(SubstractVectors(lightnings[i].globalPosition, Point));
	CoordinateStruct halfwayVector = Normalize(cameraDirection + lightDirection);


	////////////////////////////
	float lightDistance = GetVectorLength(SubstractVectors(lightnings[i].globalPosition, Point));
	float attentuation = 1.0 / (lightDistance * lightDistance);
	CoordinateStruct radiance = lightnings[i].LightColor * attentuation;

	//////
	CoordinateStruct F0 = { 0.04f,0.04f,0.04f };
	CoordinateStruct albedoVec = { albedo, albedo,albedo };
	F0 = getMix(F0, albedoVec, metallic);
	CoordinateStruct F = fresnelSchlick(getMax(DotProduct(halfwayVector, cameraDirection), 0.0f), F0);

	return CoordinateStruct();
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
	result = lightDirection -  hitNormal * (2 * DotProduct(lightDirection, hitNormal));
	return result;
}

CoordinateStruct fresnelSchlick(float cosTheta, CoordinateStruct F0) // F0 поверхностное отражение при нулевом падении
{
	CoordinateStruct tempSub = { 1.0 - F0.x,1.0 - F0.y,1.0 - F0.z };
	return F0 + (tempSub) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}
