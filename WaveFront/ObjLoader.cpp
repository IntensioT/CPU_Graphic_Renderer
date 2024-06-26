#include "ObjLoader.h"

void ObjLoader::_readFile()
{
	std::string line;

	std::ifstream file(filePath);

	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			_parseLine(line + '\n');
		}
	}
	file.close();
}


void ObjLoader::_parseLine(std::string line)
{
	char coordinates[CoordMaxLength];
	CoordinateStruct coordStr;

	if (line[0] == 'v' && line[1] == ' ')
	{
		int i = 2;
		int j = 0;
		_clearArray(coordinates);

		//X parsing
		while (line[i] != ' ' && j < CoordMaxLength)
		{
			coordinates[j++] = line[i++];
		}
		coordStr.x = _convertCharArrayToFloat(coordinates);
		_clearArray(coordinates);

		//Y parsing
		i++;
		j = 0;
		while (line[i] != ' ' && j < CoordMaxLength)
		{
			coordinates[j++] = line[i++];
		}
		coordStr.y = _convertCharArrayToFloat(coordinates);
		_clearArray(coordinates);

		//Z parsing
		i++;
		j = 0;
		while (line[i] != ' ' && line[i] != '\n' && j < CoordMaxLength)
		{
			coordinates[j++] = line[i++];
		}
		coordStr.z = _convertCharArrayToFloat(coordinates);

		_vertexVector.push_back(coordStr);
	}

	if (line[0] == 'v' && line[1] == 'n' && line[2] == ' ')
	{
		int i = 3;
		int j = 0;
		_clearArray(coordinates);

		//X parsing
		while (line[i] != ' ' && j < CoordMaxLength)
		{
			coordinates[j++] = line[i++];
		}
		coordStr.x = _convertCharArrayToFloat(coordinates);
		_clearArray(coordinates);

		//Y parsing
		i++;
		j = 0;
		while (line[i] != ' ' && j < CoordMaxLength)
		{
			coordinates[j++] = line[i++];
		}
		coordStr.y = _convertCharArrayToFloat(coordinates);
		_clearArray(coordinates);

		//Z parsing
		i++;
		j = 0;
		while (line[i] != ' ' && line[i] != '\n' && j < CoordMaxLength)
		{
			coordinates[j++] = line[i++];
		}
		coordStr.z = _convertCharArrayToFloat(coordinates);

		_normalVector.push_back(coordStr);
	}
	///////////////////////////////////////////////////////////////////
	if (line[0] == 'v' && line[1] == 't' && line[2] == ' ')
	{
		int i = 3;
		int j = 0;
		_clearArray(coordinates);

		//X parsing
		while (line[i] != ' ' && j < CoordMaxLength)
		{
			coordinates[j++] = line[i++];
		}
		coordStr.x = _convertCharArrayToFloat(coordinates);
		_clearArray(coordinates);

		//Y parsing
		i++;
		j = 0;
		while (line[i] != ' ' && line[i] != '\n' && j < CoordMaxLength)
		{
			coordinates[j++] = line[i++];
		}
		coordStr.y = _convertCharArrayToFloat(coordinates);

		_textureVector.push_back(coordStr);
	}
	///////////////////////////////////////////////////////////////////
	if (line[0] == 'u' && line[1] == 's' && line[2] == 'e' && 
		line[3] == 'm' && line[4] == 't' && line[5] == 'l' && line[6] == ' ')
	{
		int i = 7;
		int j = 0;
		_clearArray(coordinates);

		//name parsing
		while (line[i] != ' ' && line[i] != '\n' && j < CoordMaxLength)
		{
			coordinates[j++] = line[i++];
		}
		_mtlVector.push_back(coordinates);
		mtlSteps.push_back(_textureIndicies.size());

	}
	//////////////////////////////////////////////////////////////////////////
	if (line[0] == 'f' && line[1] == ' ')
	{
		int i = 2;
		int j = 0;
		//int isIndex = 1;
		_clearArray(coordinates);


		//First coord parsing
		while (i < line.length() && line[i] != '/' && j < CoordMaxLength)
		{
			coordinates[j++] = line[i];
			i++;
		}
		_indexes.push_back(_convertCharArrayToFloat(coordinates));
		_clearArray(coordinates);

		i++;
		j = 0;

		while (i < line.length() && line[i] != '/')
		{
			coordinates[j++] = line[i];
			i++;
		}
		_textureIndicies.push_back(_convertCharArrayToFloat(coordinates));
		_clearArray(coordinates);

		j = 0;
		i++;
		while (i < line.length() && line[i] != ' ')
		{
			coordinates[j++] = line[i];
			i++;
		}
		_normalIndexes.push_back(_convertCharArrayToFloat(coordinates));
		_clearArray(coordinates);

		//Second coord parsing
		i++;
		j = 0;
		while (i < line.length() && line[i] != '/' && j < CoordMaxLength)
		{
			coordinates[j++] = line[i];
			i++;
		}
		_indexes.push_back(_convertCharArrayToFloat(coordinates));
		_clearArray(coordinates);

		i++;
		j = 0;

		while (i < line.length() && line[i] != '/')
		{
			coordinates[j++] = line[i];
			i++;
		}
		_textureIndicies.push_back(_convertCharArrayToFloat(coordinates));
		_clearArray(coordinates);

		i++;
		j = 0;

		while (i < line.length() && line[i] != ' ')
		{
			coordinates[j++] = line[i];
			i++;
		}
		_normalIndexes.push_back(_convertCharArrayToFloat(coordinates));
		_clearArray(coordinates);

		//Third coord parsing
		i++;
		j = 0;
			while (i < line.length() && line[i] != '/' && j < CoordMaxLength)
			{
				coordinates[j++] = line[i];
				i++;
			}
		_indexes.push_back(_convertCharArrayToFloat(coordinates));
		_clearArray(coordinates);

		i++;
		j = 0;

		while (i < line.length() && line[i] != '/')
		{
			coordinates[j++] = line[i];
			i++;
		}
		_textureIndicies.push_back(_convertCharArrayToFloat(coordinates));
		_clearArray(coordinates);
		i++;
		j = 0;

		while (i < line.length() && line[i] != ' ' && line[i] != '\n' && j < CoordMaxLength)
		{
			coordinates[j++] = line[i];
			i++;
		}
		_normalIndexes.push_back(_convertCharArrayToFloat(coordinates));
	}
}

void ObjLoader::_clearArray(char* arr)
{
	std::memset(arr, 0, CoordMaxLength);
}

float ObjLoader::_convertCharArrayToFloat(char* arr)
{
	float result = static_cast<float>(std::atof(arr));
	return result;
}

std::vector<int> ObjLoader::GetMtlSteps()
{
	return mtlSteps;
}

std::vector<CoordinateStruct> ObjLoader::GetVetrexVector()
{
	_readFile();
	return _vertexVector;
}

std::vector<int> ObjLoader::GetIndexes()
{
	return _indexes;
}

std::vector<int> ObjLoader::GetNormalIndexes()
{
	return _normalIndexes;
}


std::vector<CoordinateStruct> ObjLoader::GetNormals()
{
	return _normalVector;
}

std::vector<CoordinateStruct> ObjLoader::GetTexturesVector()
{
	return _textureVector;
}

std::vector<int> ObjLoader::GetTextureCoordinateIndicies()
{
	return _textureIndicies;
}
