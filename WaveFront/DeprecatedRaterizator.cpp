//void Rasterizator::DrawPolygonBarycentric(const Triangle& polygon, std::vector<PointLightStruct> lightnings, CoordinateStruct& CameraGlobalCoordinates, void* frameBuffer, void* depthBuffer, RGBQUAD color)
//{
//	RectangleStruct rect = FindTriangleBoundingRectangle2D(polygon);
//
//	float w0, w1, w2, area;
//
//	area = edgeFunction(polygon.vectors[0], polygon.vectors[1], polygon.vectors[2].x, polygon.vectors[2].y);
//
//
//	for (int y = rect.top; y <= rect.bottom; y++)
//	{
//		for (int x = rect.left; x <= rect.right; x++)
//		{
//
//			w0 = edgeFunction(polygon.vectors[1], polygon.vectors[2], x, y);
//			w1 = edgeFunction(polygon.vectors[2], polygon.vectors[0], x, y);
//			w2 = edgeFunction(polygon.vectors[0], polygon.vectors[1], x, y);
//
//			if ((w0 >= 0 && w1 >= 0 && w2 >= 0) || (w0 < 0 && w1 < 0 && w2 < 0))
//			{
//				w0 /= area;
//				w1 /= area;
//				//w2 /= area;
//				w2 = 1 - w0 - w1;
//
//
//
//				float oneOverZ = polygon.vectors[0].z * w0 + polygon.vectors[1].z * w1 + polygon.vectors[2].z * w2;
//				float z = 1 / (-oneOverZ);
//				// TODO : Lock
//				if (z < reinterpret_cast<float*>(depthBuffer)[y * FrameWidth + x])
//				{
//					reinterpret_cast<float*>(depthBuffer)[y * FrameWidth + x] = z;
//
//					///////////////////////////////////////////////////////////////////////////////////////////////////
//					float curXInGlobal = polygon.vectorsInGlobal[0].x * w0 + polygon.vectorsInGlobal[1].x * w1 + polygon.vectorsInGlobal[2].x * w2;
//					float curYInGlobal = polygon.vectorsInGlobal[0].y * w0 + polygon.vectorsInGlobal[1].y * w1 + polygon.vectorsInGlobal[2].y * w2;
//					float curZInGlobal = polygon.vectorsInGlobal[0].z * w0 + polygon.vectorsInGlobal[1].z * w1 + polygon.vectorsInGlobal[2].z * w2;
//					CoordinateStruct curPointInGlobal = { curXInGlobal, curYInGlobal, curZInGlobal };
//
//					float curXNormalInGlobal = polygon.vectorsInGlobal[0].normal.x * w0 + polygon.vectorsInGlobal[1].normal.x * w1 + polygon.vectorsInGlobal[2].normal.x * w2;
//					float curYNormalInGlobal = polygon.vectorsInGlobal[0].normal.y * w0 + polygon.vectorsInGlobal[1].normal.y * w1 + polygon.vectorsInGlobal[2].normal.y * w2;
//					float curZNormalInGlobal = polygon.vectorsInGlobal[0].normal.z * w0 + polygon.vectorsInGlobal[1].normal.z * w1 + polygon.vectorsInGlobal[2].normal.z * w2;
//					CoordinateStruct hitNormal = { curXNormalInGlobal, curYNormalInGlobal, curZNormalInGlobal };
//
//					CoordinateStruct hitColor = calculatePhongLight(curPointInGlobal, hitNormal, CameraGlobalCoordinates, lightnings);
//					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//					RGBQUAD lightedColor;
//					lightedColor.rgbBlue = clamp(color.rgbBlue * hitColor.x, 0.0f, 255.0f);
//					lightedColor.rgbGreen = clamp(color.rgbGreen * hitColor.y, 0.0f, 255.0f);
//					lightedColor.rgbRed = clamp(color.rgbRed * hitColor.z, 0.0f, 255.0f);
//
//					SetPoint(frameBuffer, x, y, lightedColor);
//
//				}
//			}
//		}
//	}
//}

//void Rasterizator::DrawPolygonPBR(const Triangle& polygon, std::vector<PointLightStruct> lightnings, CoordinateStruct& CameraGlobalCoordinates, void* frameBuffer, void* depthBuffer, 
//	RGBQUAD color, CoordinateStruct materialParams, CoordinateStruct& material)
//{
//	RectangleStruct rect = FindTriangleBoundingRectangle2D(polygon);
//
//	float w0, w1, w2, area;
//
//	area = edgeFunction(polygon.vectors[0], polygon.vectors[1], polygon.vectors[2].x, polygon.vectors[2].y);
//
//
//	for (int y = rect.top; y <= rect.bottom; y++)
//	{
//		for (int x = rect.left; x <= rect.right; x++)
//		{
//
//			w0 = edgeFunction(polygon.vectors[1], polygon.vectors[2], x, y);
//			w1 = edgeFunction(polygon.vectors[2], polygon.vectors[0], x, y);
//			w2 = edgeFunction(polygon.vectors[0], polygon.vectors[1], x, y);
//
//			if ((w0 >= 0 && w1 >= 0 && w2 >= 0) || (w0 < 0 && w1 < 0 && w2 < 0))
//			{
//				w0 /= area;
//				w1 /= area;
//				//w2 /= area;
//				w2 = 1 - w0 - w1;
//
//
//
//				float oneOverZ = polygon.vectors[0].z * w0 + polygon.vectors[1].z * w1 + polygon.vectors[2].z * w2;
//				float z = 1 / (-oneOverZ);
//				// TODO : Lock
//				if (z < reinterpret_cast<float*>(depthBuffer)[y * FrameWidth + x])
//				{
//					reinterpret_cast<float*>(depthBuffer)[y * FrameWidth + x] = z;
//
//					///////////////////////////////////////////////////////////////////////////////////////////////////
//					float curXInGlobal = polygon.vectorsInGlobal[0].x * w0 + polygon.vectorsInGlobal[1].x * w1 + polygon.vectorsInGlobal[2].x * w2;
//					float curYInGlobal = polygon.vectorsInGlobal[0].y * w0 + polygon.vectorsInGlobal[1].y * w1 + polygon.vectorsInGlobal[2].y * w2;
//					float curZInGlobal = polygon.vectorsInGlobal[0].z * w0 + polygon.vectorsInGlobal[1].z * w1 + polygon.vectorsInGlobal[2].z * w2;
//					CoordinateStruct curPointInGlobal = { curXInGlobal, curYInGlobal, curZInGlobal };
//
//					float curXNormalInGlobal = polygon.vectorsInGlobal[0].normal.x * w0 + polygon.vectorsInGlobal[1].normal.x * w1 + polygon.vectorsInGlobal[2].normal.x * w2;
//					float curYNormalInGlobal = polygon.vectorsInGlobal[0].normal.y * w0 + polygon.vectorsInGlobal[1].normal.y * w1 + polygon.vectorsInGlobal[2].normal.y * w2;
//					float curZNormalInGlobal = polygon.vectorsInGlobal[0].normal.z * w0 + polygon.vectorsInGlobal[1].normal.z * w1 + polygon.vectorsInGlobal[2].normal.z * w2;
//					CoordinateStruct hitNormal = { curXNormalInGlobal, curYNormalInGlobal, curZNormalInGlobal };
//
//					//CoordinateStruct albedo = { 255,255,255 };
//					CoordinateStruct albedo = { 200,200,200 };
//
//					//CoordinateStruct hitColorPBR = calculatePBRLight(curPointInGlobal, hitNormal, CameraGlobalCoordinates, lightnings, albedo, 0.1f, 0.3f, 1.0f);
//					CoordinateStruct hitColorPBR = calculatePBRLight(curPointInGlobal, hitNormal, CameraGlobalCoordinates, lightnings, albedo, materialParams.x, materialParams.y, materialParams.z, material);
//					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//					RGBQUAD lightedColor;
//
//					lightedColor.rgbBlue = clamp(color.rgbBlue * hitColorPBR.x, 0.0f, 255.0f);
//					lightedColor.rgbGreen = clamp(color.rgbGreen * hitColorPBR.y, 0.0f, 255.0f);
//					lightedColor.rgbRed = clamp(color.rgbRed * hitColorPBR.z, 0.0f, 255.0f);
//
//					SetPoint(frameBuffer, x, y, lightedColor);
//
//				}
//			}
//		}
//	}
//}

//void Rasterizator::DrawPolygonBarycentricTexture(const Triangle& polygon, std::vector<PointLightStruct> lightnings, CoordinateStruct& CameraGlobalCoordinates, 
//	void* frameBuffer, void* depthBuffer, RGBQUAD color, TextureStruct& texture)
//{
//	RectangleStruct rect = FindTriangleBoundingRectangle2D(polygon);
//
//	float w0, w1, w2, area;
//
//	area = edgeFunction(polygon.vectors[0], polygon.vectors[1], polygon.vectors[2].x, polygon.vectors[2].y);
//
//	for (int y = rect.top; y <= rect.bottom; y++)
//	{
//		for (int x = rect.left; x <= rect.right; x++)
//		{
//
//			w0 = edgeFunction(polygon.vectors[1], polygon.vectors[2], x, y);
//			w1 = edgeFunction(polygon.vectors[2], polygon.vectors[0], x, y);
//			w2 = edgeFunction(polygon.vectors[0], polygon.vectors[1], x, y);
//
//			if ((w0 >= 0 && w1 >= 0 && w2 >= 0) || (w0 < 0 && w1 < 0 && w2 < 0))
//			{
//				w0 /= area;
//				w1 /= area;
//				w2 = 1 - w0 - w1;
//
//
//
//				float oneOverZ = polygon.vectors[0].z * w0 + polygon.vectors[1].z * w1 + polygon.vectors[2].z * w2;
//				float z = 1 / (-oneOverZ);
//				// TODO : Lock
//				if (z < reinterpret_cast<float*>(depthBuffer)[y * FrameWidth + x])
//				{
//					reinterpret_cast<float*>(depthBuffer)[y * FrameWidth + x] = z;
//
//					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//					float Tc_over_Zc_forU = w0 * (polygon.vectors[0].texture.x * polygon.vectorsInGlobal[0].w) + w1 * (polygon.vectors[1].texture.x * polygon.vectorsInGlobal[1].w) + w2 * (polygon.vectors[2].texture.x * polygon.vectorsInGlobal[2].w);
//					float Tc_over_Zc_forV = w0 * (polygon.vectors[0].texture.y * polygon.vectorsInGlobal[0].w) + w1 * (polygon.vectors[1].texture.y * polygon.vectorsInGlobal[1].w) + w2 * (polygon.vectors[2].texture.y * polygon.vectorsInGlobal[2].w);
//
//					float interpolatedInvZ = w0 * polygon.vectorsInGlobal[0].w + w1 * polygon.vectorsInGlobal[1].w + w2 * polygon.vectorsInGlobal[2].w;
//
//					float normalizedTexU = Tc_over_Zc_forU / interpolatedInvZ;
//					float normalizedTexV = Tc_over_Zc_forV / interpolatedInvZ;
//
//
//					float texelX = normalizedTexU * texture.textureWidth;
//					float texelY = normalizedTexV * texture.textureHeight;
//
//
//					int pixel_index = (int)texelY * texture.textureWidth * texture.textureChannels + (int)texelX * texture.textureChannels;
//
//					unsigned char red = texture.textureData[pixel_index];
//					unsigned char green = texture.textureData[pixel_index + 1];
//					unsigned char blue = texture.textureData[pixel_index + 2];
//					unsigned char alpha = (texture.textureChannels == 4) ? texture.textureData[pixel_index + 3] : 255;
//
//					/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//					RGBQUAD finalColor;
//					finalColor.rgbRed = /*color.rgbRed **/ red /** alpha + backgroundColor.rgbRed * backgroundAlpha * (1 - alpha)*/;
//					finalColor.rgbGreen = /*color.rgbGreen * */green /** alpha /*+ backgroundColor.rgbGreen * backgroundAlpha * (1 - alpha)*/;
//					finalColor.rgbBlue = /*color.rgbBlue **/ blue /** alpha /*+ backgroundColor.rgbBlue * backgroundAlpha * (1 - alpha)*/;
//
//					SetPoint(frameBuffer, x, y, finalColor);
//				}
//			}
//		}
//	}
//}


//void Rasterizator::DrawPolygonBarycentricTextureWithLight(const Triangle& polygon, std::vector<PointLightStruct> lightnings, CoordinateStruct& CameraGlobalCoordinates, void* frameBuffer, void* depthBuffer, RGBQUAD color, TextureStruct& texture)
//{
//	RectangleStruct rect = FindTriangleBoundingRectangle2D(polygon);
//
//	float w0, w1, w2, area;
//
//	area = edgeFunction(polygon.vectors[0], polygon.vectors[1], polygon.vectors[2].x, polygon.vectors[2].y);
//
//
//	for (int y = rect.top; y <= rect.bottom; y++)
//	{
//		for (int x = rect.left; x <= rect.right; x++)
//		{
//
//			w0 = edgeFunction(polygon.vectors[1], polygon.vectors[2], x, y);
//			w1 = edgeFunction(polygon.vectors[2], polygon.vectors[0], x, y);
//			w2 = edgeFunction(polygon.vectors[0], polygon.vectors[1], x, y);
//
//			if ((w0 >= 0 && w1 >= 0 && w2 >= 0) || (w0 < 0 && w1 < 0 && w2 < 0))
//			{
//				w0 /= area;
//				w1 /= area;
//				w2 = 1 - w0 - w1;
//
//
//
//				float oneOverZ = polygon.vectors[0].z * w0 + polygon.vectors[1].z * w1 + polygon.vectors[2].z * w2;
//				float z = 1 / (-oneOverZ);
//				// TODO : Lock
//				if (z < reinterpret_cast<float*>(depthBuffer)[y * FrameWidth + x])
//				{
//					reinterpret_cast<float*>(depthBuffer)[y * FrameWidth + x] = z;
//
//					///////////////////////////////////////////////////////////////////////////////////////////////////
//					float curXInGlobal = polygon.vectorsInGlobal[0].x * w0 + polygon.vectorsInGlobal[1].x * w1 + polygon.vectorsInGlobal[2].x * w2;
//					float curYInGlobal = polygon.vectorsInGlobal[0].y * w0 + polygon.vectorsInGlobal[1].y * w1 + polygon.vectorsInGlobal[2].y * w2;
//					float curZInGlobal = polygon.vectorsInGlobal[0].z * w0 + polygon.vectorsInGlobal[1].z * w1 + polygon.vectorsInGlobal[2].z * w2;
//					CoordinateStruct curPointInGlobal = { curXInGlobal, curYInGlobal, curZInGlobal };
//
//					float curXNormalInGlobal = polygon.vectorsInGlobal[0].normal.x * w0 + polygon.vectorsInGlobal[1].normal.x * w1 + polygon.vectorsInGlobal[2].normal.x * w2;
//					float curYNormalInGlobal = polygon.vectorsInGlobal[0].normal.y * w0 + polygon.vectorsInGlobal[1].normal.y * w1 + polygon.vectorsInGlobal[2].normal.y * w2;
//					float curZNormalInGlobal = polygon.vectorsInGlobal[0].normal.z * w0 + polygon.vectorsInGlobal[1].normal.z * w1 + polygon.vectorsInGlobal[2].normal.z * w2;
//					CoordinateStruct hitNormal = { curXNormalInGlobal, curYNormalInGlobal, curZNormalInGlobal };
//
//					CoordinateStruct hitColor = calculatePhongLight(curPointInGlobal, hitNormal, CameraGlobalCoordinates, lightnings);
//					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//					float Tc_over_Zc_forU = w0 * (polygon.vectors[0].texture.x * polygon.vectorsInGlobal[0].w) + w1 * (polygon.vectors[1].texture.x * polygon.vectorsInGlobal[1].w) + w2 * (polygon.vectors[2].texture.x * polygon.vectorsInGlobal[2].w);
//					float Tc_over_Zc_forV = w0 * (polygon.vectors[0].texture.y * polygon.vectorsInGlobal[0].w) + w1 * (polygon.vectors[1].texture.y * polygon.vectorsInGlobal[1].w) + w2 * (polygon.vectors[2].texture.y * polygon.vectorsInGlobal[2].w);
//
//					float interpolated_inv_Z = w0 * polygon.vectorsInGlobal[0].w + w1 * polygon.vectorsInGlobal[1].w + w2 * polygon.vectorsInGlobal[2].w;
//
//					float u = Tc_over_Zc_forU / interpolated_inv_Z;
//					float v = Tc_over_Zc_forV / interpolated_inv_Z;
//
//					float texX = u * texture.textureWidth;
//					float texY = v * texture.textureHeight;
//
//					int pixel_index = (int)texY * texture.textureWidth * texture.textureChannels + (int)texX * texture.textureChannels;
//
//					unsigned char red = texture.textureData[pixel_index];
//					unsigned char green = texture.textureData[pixel_index + 1];
//					unsigned char blue = texture.textureData[pixel_index + 2];
//					unsigned char alpha = (texture.textureChannels == 4) ? texture.textureData[pixel_index + 3] : 255;
//
//					RGBQUAD finalColor;
//					finalColor.rgbRed = red;
//					finalColor.rgbGreen = green;
//					finalColor.rgbBlue = blue;
//
//
//					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//					RGBQUAD lightedColor;
//
//					lightedColor.rgbBlue = clamp(hitColor.x * finalColor.rgbBlue, 0.0f, 255.0f);
//					lightedColor.rgbGreen = clamp(hitColor.y * finalColor.rgbGreen, 0.0f, 255.0f);
//					lightedColor.rgbRed = clamp(hitColor.z * finalColor.rgbRed, 0.0f, 255.0f);
//
//					SetPoint(frameBuffer, x, y, lightedColor);
//
//				}
//			}
//		}
//	}
//}

//RGBQUAD Rasterizator::_calculateTextureColor(const Triangle& polygon, float w0, float w1, float w2,
//	TextureStruct& texture, int x, int y)
//{
//	float Tc_over_Zc_forU = w0 * (polygon.vectors[0].texture.x * polygon.vectorsInGlobal[0].w) +
//		w1 * (polygon.vectors[1].texture.x * polygon.vectorsInGlobal[1].w) +
//		w2 * (polygon.vectors[2].texture.x * polygon.vectorsInGlobal[2].w);
//
//	float Tc_over_Zc_forV = w0 * (polygon.vectors[0].texture.y * polygon.vectorsInGlobal[0].w) +
//		w1 * (polygon.vectors[1].texture.y * polygon.vectorsInGlobal[1].w) +
//		w2 * (polygon.vectors[2].texture.y * polygon.vectorsInGlobal[2].w);
//
//	float interpolatedInvZ = w0 * polygon.vectorsInGlobal[0].w + w1 * polygon.vectorsInGlobal[1].w + w2 * polygon.vectorsInGlobal[2].w;
//
//	float normalizedTexU = Tc_over_Zc_forU / interpolatedInvZ;
//	float normalizedTexV = Tc_over_Zc_forV / interpolatedInvZ;
//
//	float texelX = normalizedTexU * texture.textureWidth;
//	float texelY = normalizedTexV * texture.textureHeight;
//
//	int pixel_index = (int)texelY * texture.textureWidth * texture.textureChannels + (int)texelX * texture.textureChannels;
//
//	unsigned char red = texture.textureData[pixel_index];
//	unsigned char green = texture.textureData[pixel_index + 1];
//	unsigned char blue = texture.textureData[pixel_index + 2];
//	unsigned char alpha = (texture.textureChannels == 4) ? texture.textureData[pixel_index + 3] : 255;
//
//	RGBQUAD finalColor;
//	finalColor.rgbRed = red;
//	finalColor.rgbGreen = green;
//	finalColor.rgbBlue = blue;
//
//	return finalColor;
//}


//void Rasterizator::DrawPolygonBarycentricTextureWithBillinearFiltration(const Triangle& polygon, std::vector<PointLightStruct> lightnings, CoordinateStruct& CameraGlobalCoordinates, void* frameBuffer, void* depthBuffer, RGBQUAD color, TextureStruct& texture)
//{
//	RectangleStruct rect = FindTriangleBoundingRectangle2D(polygon);
//
//	float w0, w1, w2, area;
//
//	area = edgeFunction(polygon.vectors[0], polygon.vectors[1], polygon.vectors[2].x, polygon.vectors[2].y);
//
//
//	for (int y = rect.top; y <= rect.bottom; y++)
//	{
//		for (int x = rect.left; x <= rect.right; x++)
//		{
//
//			w0 = edgeFunction(polygon.vectors[1], polygon.vectors[2], x, y);
//			w1 = edgeFunction(polygon.vectors[2], polygon.vectors[0], x, y);
//			w2 = edgeFunction(polygon.vectors[0], polygon.vectors[1], x, y);
//
//			if ((w0 >= 0 && w1 >= 0 && w2 >= 0) || (w0 < 0 && w1 < 0 && w2 < 0))
//			{
//				w0 /= area;
//				w1 /= area;
//				w2 = 1 - w0 - w1;
//
//				float oneOverZ = polygon.vectors[0].z * w0 + polygon.vectors[1].z * w1 + polygon.vectors[2].z * w2;
//				float z = 1 / (-oneOverZ);
//				// TODO : Lock
//				if (z < reinterpret_cast<float*>(depthBuffer)[y * FrameWidth + x])
//				{
//					reinterpret_cast<float*>(depthBuffer)[y * FrameWidth + x] = z;
//
//					///////////////////////////////////////////////////////////////////////////////////////////////////
//					float curXInGlobal = polygon.vectorsInGlobal[0].x * w0 + polygon.vectorsInGlobal[1].x * w1 + polygon.vectorsInGlobal[2].x * w2;
//					float curYInGlobal = polygon.vectorsInGlobal[0].y * w0 + polygon.vectorsInGlobal[1].y * w1 + polygon.vectorsInGlobal[2].y * w2;
//					float curZInGlobal = polygon.vectorsInGlobal[0].z * w0 + polygon.vectorsInGlobal[1].z * w1 + polygon.vectorsInGlobal[2].z * w2;
//					CoordinateStruct curPointInGlobal = { curXInGlobal, curYInGlobal, curZInGlobal };
//
//					float curXNormalInGlobal = polygon.vectorsInGlobal[0].normal.x * w0 + polygon.vectorsInGlobal[1].normal.x * w1 + polygon.vectorsInGlobal[2].normal.x * w2;
//					float curYNormalInGlobal = polygon.vectorsInGlobal[0].normal.y * w0 + polygon.vectorsInGlobal[1].normal.y * w1 + polygon.vectorsInGlobal[2].normal.y * w2;
//					float curZNormalInGlobal = polygon.vectorsInGlobal[0].normal.z * w0 + polygon.vectorsInGlobal[1].normal.z * w1 + polygon.vectorsInGlobal[2].normal.z * w2;
//					CoordinateStruct hitNormal = { curXNormalInGlobal, curYNormalInGlobal, curZNormalInGlobal };
//
//					CoordinateStruct hitColor = calculatePhongLight(curPointInGlobal, hitNormal, CameraGlobalCoordinates, lightnings);
//					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//					float Tc_over_Zc_forU = w0 * (polygon.vectors[0].texture.x * polygon.vectorsInGlobal[0].w) + w1 * (polygon.vectors[1].texture.x * polygon.vectorsInGlobal[1].w) + w2 * (polygon.vectors[2].texture.x * polygon.vectorsInGlobal[2].w);
//					float Tc_over_Zc_forV = w0 * (polygon.vectors[0].texture.y * polygon.vectorsInGlobal[0].w) + w1 * (polygon.vectors[1].texture.y * polygon.vectorsInGlobal[1].w) + w2 * (polygon.vectors[2].texture.y * polygon.vectorsInGlobal[2].w);
//
//					float interpolated_inv_Z = w0 * polygon.vectorsInGlobal[0].w + w1 * polygon.vectorsInGlobal[1].w + w2 * polygon.vectorsInGlobal[2].w;
//
//					float u = Tc_over_Zc_forU / interpolated_inv_Z;
//					float v = Tc_over_Zc_forV / interpolated_inv_Z;
//
//
//					float texX = u * texture.textureWidth;
//					float texY = v * texture.textureHeight;
//
//					//  Пиксельные координаты текстуры (texX, texY) для четырех ближайших текселей вокруг (u, v)
//					int x1 = (int)floor(texX);
//					int y1 = (int)floor(texY);
//					int x2 = (int)ceil(texX);
//					int y2 = (int)ceil(texY);
//
//					// Вычислить весовые коэффициенты (s, t) для линейной интерполяции между текселями.
//					float int_part;
//					float s = std::modf(texX, &int_part);
//					float t = std::modf(texY, &int_part);
//
//					int pixel_index1 = (y1 * texture.textureWidth + x1) * texture.textureChannels;
//					int pixel_index2 = (y1 * texture.textureWidth + x2) * texture.textureChannels;
//					int pixel_index3 = (y2 * texture.textureWidth + x1) * texture.textureChannels;
//					int pixel_index4 = (y2 * texture.textureWidth + x2) * texture.textureChannels;
//
//					// Вычислить цвета четырех ближайших текселей, используя пиксельные координаты
//					unsigned char red1 = texture.textureData[pixel_index1];
//					unsigned char green1 = texture.textureData[pixel_index1 + 1];
//					unsigned char blue1 = texture.textureData[pixel_index1 + 2];
//					unsigned char alpha1 = (texture.textureChannels == 4) ? texture.textureData[pixel_index1 + 3] : 255;
//
//					unsigned char red2 = texture.textureData[pixel_index2];
//					unsigned char green2 = texture.textureData[pixel_index2 + 1];
//					unsigned char blue2 = texture.textureData[pixel_index2 + 2];
//					unsigned char alpha2 = (texture.textureChannels == 4) ? texture.textureData[pixel_index2 + 3] : 255;
//
//					unsigned char red3 = texture.textureData[pixel_index3];
//					unsigned char green3 = texture.textureData[pixel_index3 + 1];
//					unsigned char blue3 = texture.textureData[pixel_index3 + 2];
//					unsigned char alpha3 = (texture.textureChannels == 4) ? texture.textureData[pixel_index3 + 3] : 255;
//
//					unsigned char red4 = texture.textureData[pixel_index4];
//					unsigned char green4 = texture.textureData[pixel_index4 + 1];
//					unsigned char blue4 = texture.textureData[pixel_index4 + 2];
//					unsigned char alpha4 = (texture.textureChannels == 4) ? texture.textureData[pixel_index4 + 3] : 255;
//
//					// Вычислить интерполированный цвет между текселями, используя весовые коэффициенты
//					unsigned char red = lerp(lerp(red1, red2, s), lerp(red3, red4, s), t);
//					unsigned char green = lerp(lerp(green1, green2, s), lerp(green3, green4, s), t);
//					unsigned char blue = lerp(lerp(blue1, blue2, s), lerp(blue3, blue4, s), t);
//					unsigned char alpha = lerp(lerp(alpha1, alpha2, s), lerp(alpha3, alpha4, s), t);
//
//					RGBQUAD finalColor;
//					finalColor.rgbRed = /*color.rgbRed **/ red /** alpha + backgroundColor.rgbRed * backgroundAlpha * (1 - alpha)*/;
//					finalColor.rgbGreen = /*color.rgbGreen * */green /** alpha /*+ backgroundColor.rgbGreen * backgroundAlpha * (1 - alpha)*/;
//					finalColor.rgbBlue = /*color.rgbBlue **/ blue /** alpha /*+ backgroundColor.rgbBlue * backgroundAlpha * (1 - alpha)*/;
//
//					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//					RGBQUAD lightedColor;
//
//					lightedColor.rgbBlue = clamp(hitColor.x * finalColor.rgbBlue, 0.0f, 255.0f);
//					lightedColor.rgbGreen = clamp(hitColor.y * finalColor.rgbGreen, 0.0f, 255.0f);
//					lightedColor.rgbRed = clamp(hitColor.z * finalColor.rgbRed, 0.0f, 255.0f);
//
//					SetPoint(frameBuffer, x, y, lightedColor);
//
//				}
//			}
//		}
//	}
//}