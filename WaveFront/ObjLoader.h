#pragma once
#include <vector>
#include <string>
#include <fstream>

#include "MathLogic.h"
	
#define CoordMaxLength 12


class ObjLoader
{

private:
	
	//std::string filePath = "D:\\Bugor\\6sem\\ComputerGraphicAlghorithms\\projects\\cube.obj";
	std::string filePath = "D:\\Bugor\\6sem\\ComputerGraphicAlghorithms\\projects\\final_v01.obj";
	//std::string filePath = "D:\\Bugor\\6sem\\ComputerGraphicAlghorithms\\projects\\shovel.obj";
	//std::string filePath = "../../assets/AtomicHeart/source/Titi/TitiTriangulated.obj";
	//std::string filePath = "../../assets/cube/source/level1/level1fixed.obj";
	std::vector<CoordinateStruct> _vertexVector;
	std::vector<CoordinateStruct> _normalVector;
	std::vector<int> _indexes;
	std::vector<int> _normalIndexes;
	void _parseLine(std::string line);
	void _readFile();
	void _clearArray(char* arr);
	float _convertCharArrayToFloat(char* arr);

public:
	std::vector<CoordinateStruct> GetVetrexVector();
	std::vector<int> GetIndexes();
	std::vector<int> GetNormalIndexes();
	std::vector<CoordinateStruct> GetNormals();
};
