#pragma once
#include <vector>
#include <string>
#include <fstream>

#define CoordMaxLength 12

struct CoordinateStruct
{
	float x, y, z;

	CoordinateStruct operator-(const CoordinateStruct& other) const {
		return CoordinateStruct{ x - other.x, y - other.y, z - other.z };
	}
};

class ObjLoader
{

private:
	
	std::string filePath = "D:\\Bugor\\6sem\\ComputerGraphicAlghorithms\\projects\\cube.obj";
	//std::string filePath = "D:\\bsuir\\6 term\\ACG\\cube.obj";
	//std::string filePath = "D:\\Bugor\\6sem\\ComputerGraphicAlghorithms\\projects\\Miyu_Akey_Rigging.obj";
	//std::string filePath = "D:\\bsuir\\6 term\\ACG\\Miyu_Akey_Rigging.obj";
	//std::string filePath = "D:\\Bugor\\6sem\\ComputerGraphicAlghorithms\\projects\\DoomCombatScene.obj";
	//std::string filePath = "D:\\Bugor\\6sem\\ComputerGraphicAlghorithms\\projects\\final_v01.obj";
	std::vector<CoordinateStruct> _vertexVector;
	std::vector<int> _indexes;
	void _parseLine(std::string line);
	void _readFile();
	void _clearArray(char* arr);
	float _convertCharArrayToFloat(char* arr);

public:
	std::vector<CoordinateStruct> GetVetrexVector();
	std::vector<int> GetIndexes();
};
