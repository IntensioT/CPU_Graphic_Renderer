#pragma once

struct TextureStruct
{
	unsigned char* textureData;
	unsigned char* metallnessData;
	unsigned char* roughnessData;
	unsigned char* AOData;
	unsigned char* specularTexturData;
	unsigned char* normalTexturData;
	int textureWidth, textureHeight, textureChannels;
};