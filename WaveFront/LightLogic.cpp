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
