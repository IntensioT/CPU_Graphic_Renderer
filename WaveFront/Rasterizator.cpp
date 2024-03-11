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
	//float z0 = std::abs(polygon.vectors[0].z);
	//float z1 = std::abs(polygon.vectors[0].z);
	//float z2 = std::abs(polygon.vectors[0].z);

	//// Вычисление значений z для вершин треугольника
	//std::vector<float> z01 = Interpolate(polygon.vectors[0].y, z0, polygon.vectors[1].y, z1);
	//std::vector<float> z12 = Interpolate(polygon.vectors[1].y, z1, polygon.vectors[2].y, z2);
	//std::vector<float> z02 = Interpolate(polygon.vectors[0].y, z0, polygon.vectors[2].y, z2);

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
}

Rasterizator::Rasterizator(int width, int height) 
{
	zBuffer.assign(height, std::vector<float>(width, std::numeric_limits<float>::max()));
	//zInterpolated.assign(height, 0.0f);

	
}


