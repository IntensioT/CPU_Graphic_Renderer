#include "Rasterizator.h"

void Rasterizator::SortYPoints(Triangle& polygon)
{
	// Сортировка точек так, что y0 <= y1 <= y2
	if (polygon.vectors[1].y < polygon.vectors[0].y) std::swap(polygon.vectors[1], polygon.vectors[0]);
	if (polygon.vectors[2].y < polygon.vectors[0].y) std::swap(polygon.vectors[2], polygon.vectors[0]);
	if (polygon.vectors[2].y < polygon.vectors[1].y) std::swap(polygon.vectors[2], polygon.vectors[1]);
}

Triangle Rasterizator::correctOrdinary(Triangle polygon)
{
	float y0 = polygon.vectors[0].y;
	float y1 = polygon.vectors[1].y;
	float y2 = polygon.vectors[2].y;

	if (y1 < y0)
	{
		SwapVectorsInPolygon(polygon, 1, 0);
	}
	if (y2 < y0)
	{
		SwapVectorsInPolygon(polygon, 2, 0);
	}
	if (y2 < y1)
	{
		SwapVectorsInPolygon(polygon, 2, 1);
	}

	return Triangle();
}

void Rasterizator::getXleftAndRight(Triangle polygon)
{
	isLeft = 0;
	// Вычисление координат x рёбер треугольника
	std::vector<float> x01 = Interpolate(polygon.vectors[0].y, polygon.vectors[0].x, polygon.vectors[1].y, polygon.vectors[1].x);
	std::vector<float> x12 = Interpolate(polygon.vectors[1].y, polygon.vectors[1].x, polygon.vectors[2].y, polygon.vectors[2].x);
	std::vector<float> x02 = Interpolate(polygon.vectors[0].y, polygon.vectors[0].x, polygon.vectors[2].y, polygon.vectors[2].x);

	// Конкатенация коротких сторон
	x01.pop_back();
	std::vector<float> x012;
	x012.insert(x012.end(), x01.begin(), x01.end());
	x012.insert(x012.end(), x12.begin(), x12.end());

	// Определяем, какая из сторон левая и правая
	int m = x012.size() / 2;
	if (x02[m] < x012[m]) {
		isLeft = 1;

		xLeft = x02;
		xRight = x012;
	}
	else {
		xLeft = x012;
		xRight = x02;
	}
}

void Rasterizator::getZLeftAndZRight(Triangle polygon)
{

	// Вычисление значений z для вершин треугольника
	std::vector<float> z01 = Interpolate(polygon.vectors[0].y, polygon.vectors[0].z, polygon.vectors[1].y, polygon.vectors[1].z);
	std::vector<float> z12 = Interpolate(polygon.vectors[1].y, polygon.vectors[1].z, polygon.vectors[2].y, polygon.vectors[2].z);
	std::vector<float> z02 = Interpolate(polygon.vectors[0].y, polygon.vectors[0].z, polygon.vectors[2].y, polygon.vectors[2].z);

	// Конкатенация значений z для коротких сторон
	z01.pop_back();
	std::vector<float> z012;
	z012.insert(z012.end(), z01.begin(), z01.end());
	z012.insert(z012.end(), z12.begin(), z12.end());

	// Определяем, какая из сторон левая и правая
	if (isLeft == 1)
	{
		zLeft = z02;
		zRight = z012;
	}
	else
	{
		zLeft = z012;
		zRight = z02;
	}
}

void Rasterizator::getHLeftAndHRight(Triangle polygon)
{
	// Вычисление значений h для вершин треугольника
	std::vector<float> h01 = Interpolate(polygon.vectors[0].y, polygon.vectors[0].shade, polygon.vectors[1].y, polygon.vectors[1].shade);
	std::vector<float> h12 = Interpolate(polygon.vectors[1].y, polygon.vectors[1].shade, polygon.vectors[2].y, polygon.vectors[2].shade);
	std::vector<float> h02 = Interpolate(polygon.vectors[0].y, polygon.vectors[0].shade, polygon.vectors[2].y, polygon.vectors[2].shade);

	// Конкатенация значений h для коротких сторон
	h01.pop_back();
	std::vector<float> h012;
	h012.insert(h012.end(), h01.begin(), h01.end());
	h012.insert(h012.end(), h12.begin(), h12.end());

	// Определяем, какая из сторон левая и правая
	if (isLeft == 1)
	{
		hLeft = h02;
		hRight = h012;
	}
	else
	{
		hLeft = h012;
		hRight = h02;
	}
}

void Rasterizator::getDiffuseLeftAndDiffuseRight(Triangle polygon)
{
	//// Вычисление значений h для вершин треугольника
	//std::vector<float> diffuse01 = Interpolate(polygon.vectors[0].y, polygon.vectors[0].diffuse., polygon.vectors[1].y, polygon.vectors[1].shade);
	//std::vector<float> diffuse01 = Interpolate(polygon.vectors[1].y, polygon.vectors[1].shade, polygon.vectors[2].y, polygon.vectors[2].shade);
	//std::vector<float> diffuse01 = Interpolate(polygon.vectors[0].y, polygon.vectors[0].shade, polygon.vectors[2].y, polygon.vectors[2].shade);

	//// Конкатенация значений h для коротких сторон
	//h01.pop_back();
	//std::vector<float> h012;
	//h012.insert(h012.end(), h01.begin(), h01.end());
	//h012.insert(h012.end(), h12.begin(), h12.end());

	//// Определяем, какая из сторон левая и правая
	//if (isLeft == 1)
	//{
	//	hLeft = h02;
	//	hRight = h012;
	//}
	//else
	//{
	//	hLeft = h012;
	//	hRight = h02;
	//}
}



std::vector<float> Rasterizator::Interpolate(float i0, float d0, float i1, float d1)
{
	std::vector<float> values;
	if (i0 == i1)
	{
		values.push_back(d0);
		return values;
	}

	float accretion = (d1 - d0) / (i1 - i0);
	float d = d0;
	float step = (i1 > i0) ? 1 : -1; // Определяем шаг инкрементации

	int imax = static_cast<int>((i1 - i0) / step) + 1;
	for (int i = 0; i < imax; i++) // Инкрементируем i с использованием шага
	//for (float i = i0; i != i1; i += step) // Инкрементируем i с использованием шага
	{
		values.push_back(d);
		d = d + accretion;
	}

	// Добавляем последнее значение, чтобы гарантировать, что d1 включено в результат
	values.push_back(d1);

	return values;
}


void Rasterizator::UpdateXleftAndXRight(Triangle& polygon)
{
	SortYPoints(polygon);
	getXleftAndRight(polygon);
	getZLeftAndZRight(polygon);
	getHLeftAndHRight(polygon);
}

//void Rasterizator::LambertShading(CoordSystem* modelCoord, Triangle curPolygon, CoordinateStruct lightPos, CoordinateStruct polygonPos)
//{
//	for (int i = 0; i < 3; i++)
//	{
//
//	}
//	CoordinateStruct normal = modelCoord->NormalizeVector(curNormal);
//	// получаем вектор направления света
//	CoordinateStruct lightDirection = modelCoord->NormalizeVector(modelCoord->SubstractVectors(lightPos, polygonPos));
//
//	// получаем скалярное произведение векторов нормали и направления света
//	float lambertTerm = (modelCoord->DotProduct(normal, lightDirection) >= 0.0) ? modelCoord->DotProduct(normal, lightDirection) : 0.0f;
//	//CoordinateStruct diffuse = { DiffuseLightColor.x * lambertTerm, DiffuseLightColor.y * lambertTerm, DiffuseLightColor.z * lambertTerm };
//	return { DiffuseLightColor.x * lambertTerm, DiffuseLightColor.y * lambertTerm, DiffuseLightColor.z * lambertTerm };
//
//	
//}


