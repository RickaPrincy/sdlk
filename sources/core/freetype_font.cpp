#include <iostream>
#include <memory>
#include <ostream>
#include <sdlk/core/app.hpp>
#include <sdlk/core/freetype_font.hpp>
#include <stdexcept>

namespace sdlk
{
	freetype_font::freetype_font(std::string font_path, int font_size, int char_to_load)
	{
		if (FT_New_Face(app::get_ft_library(), font_path.c_str(), 0, &this->m_face))
		{
			throw std::runtime_error("Cannot load font " + font_path);
		}

		FT_Set_Pixel_Sizes(this->m_face, 0, font_size);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);	// disable byte-alignment restriction

		FT_Face &face = this->m_face;
		for (unsigned char c = 0; c < char_to_load; c++)
		{
			// load character glyph
			if (FT_Load_Char(this->m_face, c, FT_LOAD_RENDER))
			{
				std::cerr << "ERROR::FREETYTPE: Failed to load Glyph \n" << std::flush;
				continue;
			}

			// generate texture
			GLuint texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(GL_TEXTURE_2D,
				0,
				GL_RED,
				face->glyph->bitmap.width,
				face->glyph->bitmap.rows,
				0,
				GL_RED,
				GL_UNSIGNED_BYTE,
				face->glyph->bitmap.buffer);
			// set texture options
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			// now store character for later use
			character new_character;
			new_character.texture_id = texture;
			new_character.size = glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			new_character.bearing = glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			new_character.advance = face->glyph->advance.x;

			this->_characters.insert(std::pair<char, character>(c, std::move(new_character)));
			this->_ascender = this->m_face->size->metrics.ascender >> 6;
		}
	};

	auto freetype_font::get_ascender() const -> int
	{
		return this->_ascender;
	}

	auto freetype_font::get_face() -> FT_Face &
	{
		return this->m_face;
	}

	auto freetype_font::get_character(const char &c) -> character &
	{
		return this->_characters[c];
	}

	auto freetype_font::make(std::string font_path, int font_size, int char_to_load)
		-> std::shared_ptr<freetype_font>
	{
		return std::make_shared<freetype_font>(
			std::move(font_path), std::move(font_size), std::move(char_to_load));
	}

	freetype_font::~freetype_font()
	{
		for (const auto &[c, ch] : this->_characters)
		{
			if (ch.texture_id)
			{
				glDeleteTextures(1, &ch.texture_id);
			}
		}

		this->_characters.clear();
		FT_Done_Face(this->m_face);
	}
}  // namespace sdlk
