#pragma once
#include <vector>
#include <string>
#include <fstream>

#include "3DVectorStruct.h"

#define CoordMaxLength 12


class ObjLoader
{

private:
	
	std::string filePath = "D:\\Bugor\\6sem\\ComputerGraphicAlghorithms\\projects\\cube.obj";
	//std::string filePath = "D:\\bsuir\\6 term\\ACG\\cube.obj";
	//std::string filePath = "D:\\Bugor\\6sem\\ComputerGraphicAlghorithms\\projects\\Miyu_Akey_Rigging.obj";
	//std::string filePath = "D:\\bsuir\\6 term\\ACG\\Miyu_Akey_Rigging.obj";
	//std::string filePath = "D:\\Bugor\\6sem\\ComputerGraphicAlghorithms\\projects\\DoomCombatScene.obj";
	//std::string filePath = "D:\\Bugor\\6sem\\ComputerGraphicAlghorithms\\projects\\final_v01.obj";
	//std::string filePath = "D:\\Bugor\\6sem\\ComputerGraphicAlghorithms\\projects\\shovel.obj";
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
