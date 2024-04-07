#pragma once

#ifndef TEXTURE_LOADER_H_
#define TEXTURE_LOADER_H_

#include "TextureStruct.h"

#include <string>
#include <vector>

TextureStruct LoadTexture(const char* path);
void UnloadTexture(std::vector<TextureStruct>& textureDatas);

#endif