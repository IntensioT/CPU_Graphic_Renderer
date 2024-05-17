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