#pragma once
#include <raylib.h>
#include <unordered_map>


struct AssetManager
{

	Texture2D dirt = {};
	Texture2D textures = {};
	Texture2D frame = {};

	void loadAll();
};