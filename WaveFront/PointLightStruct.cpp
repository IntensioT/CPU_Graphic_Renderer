#include "PointLightStruct.h"

void PointLightStruct::illuminate(const CoordinateStruct& Point, CoordinateStruct& lightDirection, CoordinateStruct& lightIntensity) const
{
	lightDirection = (Point - globalPosition);
	float lightDirLength = GetVectorLength(addZeroToGetHomogeneous(lightDirection));

	//distance =  sqrt(lightDirLength);
	lightDirection = Normalize(lightDirection);
	//lightDirection.x /= distance, lightDirection.y /= distance, lightDirection.z /= distance;


	// avoid division by 0
	lightIntensity = LightColor * LightIntesity * (1 / (4 * M_PI * lightDirLength)); // коэффициент ослабления освещения с расстоянием
	// В физике закон обратных квадратов выводится из закона сохранения энергии и геометрических соображений. 
	// Предположим, что источник света испускает энергию равномерно во всех направлениях. 
	// Тогда энергия, проходящая через сферическую поверхность радиуса r, центрированную вокруг источника, будет пропорциональна площади этой поверхности, которая равна 4 * M_PI * r * r. 
	// Следовательно, интенсивность света, проходящая через единичную площадку на расстоянии r от источника, будет обратно пропорциональна площади сферы, то есть 1 / (4 * M_PI * r * r).
}
