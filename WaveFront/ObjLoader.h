#pragma once
#include <vector>
#include <string>
#include <fstream>

#include "MathLogic.h"
	
#define CoordMaxLength 12


class ObjLoader
{

private:
	
	//std::string filePath = "D:\\Bugor\\6sem\\ComputerGraphicAlghorithms\\projects\\final_v01.obj";
	//std::string filePath = "../../assets/AtomicHeart/source/Titi/TitiTriangulated.obj";
	//std::string filePath = "../../assets/cube/box.obj";
	//std::string filePath = "../../assets/madokaMachida/source/triangulated/madoka.obj";
	std::string filePath = "../../assets/Shovel Knight/shovel.obj";
	std::vector<CoordinateStruct> _vertexVector;
	std::vector<CoordinateStruct> _normalVector;
	std::vector<CoordinateStruct> _textureVector;
	std::vector<int> _indexes;
	std::vector<int> _normalIndexes;
	std::vector<int> _textureIndicies;
	void _parseLine(std::string line);
	void _readFile();
	void _clearArray(char* arr);
	float _convertCharArrayToFloat(char* arr);

public:
	std::vector<CoordinateStruct> GetVetrexVector();
	std::vector<int> GetIndexes();
	std::vector<int> GetNormalIndexes();
	std::vector<CoordinateStruct> GetNormals();
	std::vector<CoordinateStruct> GetTexturesVector();
	std::vector<int> GetTextureCoordinateIndicies();

};
