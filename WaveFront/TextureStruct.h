#pragma once

struct TextureStruct
{
	unsigned char* textureData;
	unsigned char* specularTexturData;
	unsigned char* normalTexturData;
	int textureWidth, textureHeight, textureChannels;
};