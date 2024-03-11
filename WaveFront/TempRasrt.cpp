//Triangle test1;
//test1.vectors[0] = { 300,100,0,0 };
//test1.vectors[1] = { 300,300,0,0 };
//test1.vectors[2] = { 100,300,0,0 };

//rasterizator->UpdateXleftAndXRight(test1);
//// Отрисовка горизонтальных отрезков
//for (float y = test1.vectors[0].y; y < test1.vectors[2].y; y++)
//{
//	for (float x = rasterizator->xLeft[y - test1.vectors[0].y]; x < rasterizator->xRight[y - test1.vectors[0].y]; x++)
//	{
//		SetPoint(frameBuffer, x, y, color);
//	}
//}
//Triangle test2;
//test2.vectors[0] = { 300,100,0,0 };
//test2.vectors[1] = { 300,300,0,0 };
//test2.vectors[2] = { 100,100,0,0 };

//rasterizator->UpdateXleftAndXRight(test2);
//// Отрисовка горизонтальных отрезков
//for (float y = test2.vectors[0].y; y < test2.vectors[2].y; y++)
//{
//	for (float x = rasterizator->xLeft[y - test2.vectors[0].y]; x < rasterizator->xRight[y - test2.vectors[0].y]; x++)
//	{
//		SetPoint(frameBuffer, x, y, color);
//	}
//}



//rasterizator->UpdateXleftAndXRight(test1);

//// Отрисовка горизонтальных отрезков
//for (int y = test1.vectors[0].y; y <= test1.vectors[2].y; y++) {
//	for (int x = rasterizator->xLeft[y - test1.vectors[0].y]; x <= rasterizator->xRight[y - test1.vectors[0].y]; x++) {
//		SetPoint(frameBuffer, x, y, color);
//	}
//}


//Triangle test1;
//test1.vectors[0] = { 300,100,3,0 };
//test1.vectors[1] = { 300,300,3,0 };
//test1.vectors[2] = { 100,300,3,0 };


//Triangle test2;
//test2.vectors[0] = { 400,200,5,0 };
//test2.vectors[1] = { 450,400,5,0 };
//test2.vectors[2] = { 100,200,5,0 };


//rasterizator->UpdateXleftAndXRight(test1);

//// Отрисовка горизонтальных отрезков
//for (int y = test1.vectors[0].y; y <= test1.vectors[2].y; y++) {

//	int xL = rasterizator->xLeft[y - test1.vectors[0].y];
//	int xR = rasterizator->xRight[y - test1.vectors[0].y];
//	for (int x = xL; x <= xR; x++) {
//		int zL = rasterizator->zLeft[y - test1.vectors[0].y];
//		int zR = rasterizator->zRight[y - test1.vectors[0].y];

//		float z;
//		if (xR - xL != 0)
//		{
//			z = zL + (x - xL) * (zR - zL) / (xR - xL);
//		}
//		else
//		{
//			z = zL;
//		}

//		if (z < depthBuffer[x][y])
//		{
//			SetPoint(frameBuffer, x, y, {0,255,0,0});
//			depthBuffer[x][y] = z;
//		}
//	}
//}

//rasterizator->UpdateXleftAndXRight(test2);
//// Отрисовка горизонтальных отрезков
//for (int y = test2.vectors[0].y; y <= test2.vectors[2].y; y++) {

//	int xL = rasterizator->xLeft[y - test2.vectors[0].y];
//	int xR = rasterizator->xRight[y - test2.vectors[0].y];
//	for (int x = xL; x <= xR; x++) {
//		int zL = rasterizator->zLeft[y - test2.vectors[0].y];
//		int zR = rasterizator->zRight[y - test2.vectors[0].y];

//		float z;
//		if (xR - xL != 0)
//		{
//			z = zL + (x - xL) * (zR - zL) / (xR - xL);
//		}
//		else
//		{
//			z = zL;
//		}

//		if (z < depthBuffer[x][y])
//		{
//			SetPoint(frameBuffer, x, y, {255,0,0,0});
//			depthBuffer[x][y] = z;
//		}
//	}
//}









//if (line[0] == 'f' && line[1] == ' ')
//{
//	int i = 2;
//	int j = 0;
//	int isIndex = 1;
//	_clearArray(coordinates);
//
//	////First coord parsing
//	//while (line[i] != ' ' && j < CoordMaxLength)
//	//{
//	//	if (line[i] == '/')
//	//	{
//	//		isIndex = 0;
//	//	}
//	//	if (isIndex == 1)
//	//	{
//	//		coordinates[j++] = line[i];
//	//	}
//	//	i++;
//	//}
//	//_indexes.push_back( _convertCharArrayToFloat(coordinates));
//	//_clearArray(coordinates);
//
//	//First coord parsing
//	while (line[i] != '/' && j < CoordMaxLength)
//	{
//		coordinates[j++] = line[i];
//		i++;
//	}
//	_indexes.push_back(_convertCharArrayToFloat(coordinates));
//	_clearArray(coordinates);
//
//	i++;
//	j = 0;
//
//	while (line[i] != '/')
//	{
//		i++;
//	}
//	i++;
//	while (line[i] != ' ')
//	{
//		coordinates[j++] = line[i];
//		i++;
//	}
//	_normalIndexes.push_back(_convertCharArrayToFloat(coordinates));
//	_clearArray(coordinates);
//
//
//	////Second coord parsing
//	//isIndex = 1;
//	//i++;
//	//j = 0;
//	//while (line[i] != ' ' && j < CoordMaxLength)
//	//{
//	//	if (line[i] == '/')
//	//	{
//	//		isIndex = 0;
//	//	}
//	//	if (isIndex == 1)
//	//	{
//	//		coordinates[j++] = line[i];
//	//	}
//	//	i++;
//	//}
//	//_indexes.push_back(_convertCharArrayToFloat(coordinates));
//	//_clearArray(coordinates);
//
//	//Second coord parsing
//	isIndex = 1;
//	i++;
//	j = 0;
//	while (line[i] != '/' && j < CoordMaxLength)
//	{
//		coordinates[j++] = line[i];
//		i++;
//	}
//	_indexes.push_back(_convertCharArrayToFloat(coordinates));
//	_clearArray(coordinates);
//
//	i++;
//	j = 0;
//
//	while (line[i] != '/')
//	{
//		i++;
//	}
//	i++;
//	while (line[i] != ' ')
//	{
//		coordinates[j++] = line[i];
//		i++;
//	}
//	_normalIndexes.push_back(_convertCharArrayToFloat(coordinates));
//	_clearArray(coordinates);
//
//	////Third coord parsing
//	//isIndex = 1;
//	//i++;
//	//j = 0;
//	//while (line[i] != ' ' && line[i] != '\n' && j < CoordMaxLength)
//	//{
//	//	if (line[i] == '/')
//	//	{
//	//		isIndex = 0;
//	//	}
//	//	if (isIndex == 1)
//	//	{
//	//		coordinates[j++] = line[i];
//	//	}
//	//	i++;
//	//}
//	//_indexes.push_back(_convertCharArrayToFloat(coordinates));
//
//	//Third coord parsing
//	isIndex = 1;
//	i++;
//	j = 0;
//	while (line[i] != '/' && j < CoordMaxLength)
//	{
//		coordinates[j++] = line[i];
//		i++;
//	}
//	_indexes.push_back(_convertCharArrayToFloat(coordinates));
//	_clearArray(coordinates);
//
//	i++;
//	j = 0;
//
//	while (line[i] != '/')
//	{
//		i++;
//	}
//	i++;
//	while (line[i] != ' ' && line[i] != '\n' && j < CoordMaxLength)
//	{
//		coordinates[j++] = line[i];
//		i++;
//	}
//	_normalIndexes.push_back(_convertCharArrayToFloat(coordinates));
//}