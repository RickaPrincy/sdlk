//
// Created by ricka on 2025-12-30.
//

#include "file.hpp"

#include <fstream>

namespace sdlk::file
{
	std::string read(const std::string &path)
	{
		std::ifstream file(path, std::ios::binary);
		if (!file)
		{
			throw std::runtime_error("Cannot open file: " + path);
		}

		std::ostringstream ss;
		ss << file.rdbuf();
		return ss.str();
	}
}