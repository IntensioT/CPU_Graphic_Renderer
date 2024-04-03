#define STB_IMAGE_IMPLEMENTATION
#include "ImageLoader/stb_image.h"

#include "TextureLoader.h"


TextureStruct LoadTexture(const char* path)
{
	TextureStruct result;
	/*unsigned char* textureData;
	int textureWidth, textureHeight, textureChannels;*/

	result.textureData = stbi_load(path, &result.textureWidth, &result.textureHeight, &result.textureChannels, 0);

	if (!result.textureData) {
		// 
	}
	return result;
}

void UnloadTexture(std::vector<unsigned char*>& textureDatas)
{
	for (auto i = 0; i < textureDatas.size(); i++)
	{
		stbi_image_free(textureDatas[i]);

	}
}
