#pragma once
#include <raylib.h>
#include <unordered_map>


struct AssetManager
{

	Texture2D dirt = {};

	void loadAll();
};