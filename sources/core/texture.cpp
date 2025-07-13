#include <SDL2/SDL_image.h>

#include <sdlk/core/texture.hpp>
#include <stdexcept>

namespace sdlk
{

	texture::texture(GLuint id, int width, int height) : m_id(id), m_width(width), m_height(height)
	{
	}

	std::shared_ptr<texture> texture::from_file(const std::string& path)
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

	std::shared_ptr<texture> texture::from_surface(SDL_Surface* surface)
	{
		if (!surface)
		{
			throw std::runtime_error("from_surface received null surface");
		}

		GLuint id;
		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);

		GLint format = surface->format->BytesPerPixel == 4 ? GL_RGBA : GL_RGB;

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

		return std::make_shared<texture>(id, surface->w, surface->h);
	}

	auto texture::bind(GLuint unit) const -> void
	{
		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(GL_TEXTURE_2D, this->m_id);
	}

	auto texture::get_width() const -> int
	{
		return this->m_width;
	}

	auto texture::get_height() const -> int
	{
		return this->m_height;
	}

	texture::~texture()
	{
		if (this->m_id != 0)
		{
			glDeleteTextures(1, &this->m_id);
		}
	}
}  // namespace sdlk
