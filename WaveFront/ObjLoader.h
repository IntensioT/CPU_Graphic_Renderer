#pragma once
#include <vector>
#include <string>
#include <fstream>

#define CoordMaxLength 12

struct CoordinateStruct
{
	float x, y, z;
};

class ObjLoader
{

private:
	
	std::string filePath = "D:\\Bugor\\6sem\\ComputerGraphicAlghorithms\\projects\\cube.obj";
	std::vector<CoordinateStruct> _vertexVector;
	void _parseLine(std::string line);
	void _readFile();
	void _clearArray(char* arr);
	float _convertCharArrayToFloat(char* arr);
public:
	std::vector<CoordinateStruct> GetVetrexVector();
};
