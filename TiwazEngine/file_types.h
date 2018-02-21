#pragma once

#include <string>
#include <array>

namespace Tiwaz::FileFormats
{
	template<size_t TSizeIndices> struct MeshData
	{
		std::string mesh_name = "test";
		unsigned int ints[TSizeIndices];
	};
}