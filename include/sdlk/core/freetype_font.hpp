#pragma once

#include <ft2build.h>
#include <glad/glad.h>

#include <glm/vec2.hpp>
#include <map>
#include <memory>
#include <string>
#include FT_FREETYPE_H

namespace sdlk
{

	struct character
	{
		GLuint texture_id;	   // ID handle of the glyph texture
		glm::ivec2 size;	   // Size of glyph
		glm::ivec2 bearing;	   // Offset from baseline to left/top of glyph
		unsigned int advance;  // Offset to advance to next glyph
	};

	class freetype_font
	{
	private:
		int _ascender{};
		std::map<char, character> _characters{};

	protected:
		FT_Face m_face;

	public:
		[[nodiscard]] auto get_face() -> FT_Face &;
		[[nodiscard]] auto get_character(const char &c) -> character &;
		[[nodiscard]] auto get_ascender() const -> int;
		[[nodiscard]] static auto make(std::string font_path,
			int font_size = 20,
			int char_to_load = 128) -> std::shared_ptr<freetype_font>;

		freetype_font(std::string font_path, int font_size = 20, int char_to_load = 128);
		virtual ~freetype_font();
	};
}  // namespace sdlk
