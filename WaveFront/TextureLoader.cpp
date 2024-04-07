#define STB_IMAGE_IMPLEMENTATION
#include "ImageLoader/stb_image.h"

#include "TextureLoader.h"


TextureStruct LoadTexture(const char* path)
{
	stbi_set_flip_vertically_on_load(1);
	TextureStruct result;

	result.textureData = stbi_load(path, &result.textureWidth, &result.textureHeight, &result.textureChannels, 0);

	if (!result.textureData) {
		// 
		bool sus = false;
	}
	return result;
}

void UnloadTexture(std::vector<TextureStruct>& textureDatas)
{
	for (auto i = 0; i < textureDatas.size(); i++)
	{
		stbi_image_free(textureDatas[i].textureData);
		stbi_image_free(textureDatas[i].specularTexturData);
		stbi_image_free(textureDatas[i].normalTexturData);
	}
}
