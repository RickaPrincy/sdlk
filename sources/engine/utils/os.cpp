//
// Created by ricka on 2026-05-17.
//

#include "os.hpp"
#include <stdexcept>

auto os::get_home_dir() -> std::string
{
#ifdef _WIN32
	const char* home = std::getenv("USERPROFILE");
#else
	const char* home = std::getenv("HOME");
#endif
	if(home) return std::string(home);

	throw std::runtime_error("Could not get home directory");
}
