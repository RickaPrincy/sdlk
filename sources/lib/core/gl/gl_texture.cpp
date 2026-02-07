//
// Created by ricka on 2026-01-18.
//

#include <SDL2/SDL_image.h>

#include <sdlk/core/gl/gl_texture.hpp>
#include <stdexcept>

namespace sdlk
{
	gl_texture::gl_texture(const GLuint id, const int width, const int height)
		: m_id(id),
		  m_width(width),
		  m_height(height)
	{
	}

	std::shared_ptr<gl_texture> gl_texture::from_file(const std::string& path)
	{
		SDL_Surface* surface = IMG_Load(path.c_str());
		if (!surface)
		{
			throw std::runtime_error("Failed to load image: " + path);
		}

		auto tex = from_surface(surface);
		SDL_FreeSurface(surface);
		return tex;
	}

	std::shared_ptr<gl_texture> gl_texture::from_surface(SDL_Surface* surface)
	{
		if (!surface)
		{
			throw std::runtime_error("from_surface received null surface");
		}

		GLuint id;
		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);

		const GLint format = surface->format->BytesPerPixel == 4 ? GL_RGBA : GL_RGB;

		glTexImage2D(GL_TEXTURE_2D,
			0,
			format,
			surface->w,
			surface->h,
			0,
			format,
			GL_UNSIGNED_BYTE,
			surface->pixels);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		return std::make_shared<gl_texture>(id, surface->w, surface->h);
	}

	auto gl_texture::bind(const GLuint unit) const -> void
	{
		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(GL_TEXTURE_2D, this->m_id);
	}

	auto gl_texture::get_width() const -> int
	{
		return this->m_width;
	}

	auto gl_texture::get_height() const -> int
	{
		return this->m_height;
	}

	auto gl_texture::get_id() -> GLuint&
	{
		return this->m_id;
	}

	auto gl_texture::get_ratio() const -> float
	{
		return static_cast<float>(this->m_width) / static_cast<float>(this->m_height);
	}

	gl_texture::~gl_texture()
	{
		if (this->m_id != 0)
		{
			glDeleteTextures(1, &this->m_id);
		}
	}
}  // namespace sdlk2d
