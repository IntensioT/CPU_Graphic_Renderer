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

std::vector<CoordinateStruct> ObjLoader::GetVetrexVector()
{
	_readFile();
	return _vertexVector;
}
