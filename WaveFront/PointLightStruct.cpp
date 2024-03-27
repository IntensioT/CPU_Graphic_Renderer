#include "PointLightStruct.h"

void PointLightStruct::illuminate(const CoordinateStruct& Point, CoordinateStruct& lightDirection, CoordinateStruct& lightIntensity) const
{
	lightDirection = (Point - globalPosition);
	float lightDirLength = GetVectorLength(addZeroToGetHomogeneous(lightDirection));

	//distance =  sqrt(lightDirLength);
	lightDirection = Normalize(lightDirection);
	//lightDirection.x /= distance, lightDirection.y /= distance, lightDirection.z /= distance;


	// avoid division by 0
	lightIntensity = LightColor * LightIntesity * (1 / (4 * M_PI * lightDirLength)); // коэффициента ослабления освещения с расстоянием
}
