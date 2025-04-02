#include <regex>
#include <sdlk/core/jsx.hpp>
#include <stdexcept>

namespace sdlk
{
	std::string jsx::extract_tag_name(const std::string &jsx)
	{
		std::regex tag_regex(R"(<(\w+))");
		std::smatch match;

		if (std::regex_search(jsx, match, tag_regex))
		{
			return match[1];
		}
		throw std::runtime_error("No valid tag name");
	}
}  // namespace sdlk
