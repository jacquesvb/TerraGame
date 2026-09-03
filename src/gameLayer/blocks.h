#pragma once
#include <cstdint>

struct Block
{
	enum
	{
		air = 0,
		dirt,

		BLOCKS_COUNT,
	};

	std::uint16_t type = 0;
};
// To find an element in a 2D array stored as a 1D array, you can use the formula: index = y * width + x