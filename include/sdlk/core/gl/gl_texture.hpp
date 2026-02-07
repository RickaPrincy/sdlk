#pragma once

#include <SDL2/SDL_surface.h>
#include <glad/glad.h>

#include <memory>
#include <string>

namespace sdlk
{
	class gl_texture
	{
		GLuint m_id{ 0 };
		int m_width{}, m_height{};

	public:
		gl_texture() = default;
		gl_texture(GLuint id, int width, int height);

		auto bind(GLuint unit = 0) const -> void;

		[[nodiscard]] auto get_id() -> GLuint&;
		[[nodiscard]] auto get_width() const -> int;
		[[nodiscard]] auto get_height() const -> int;
		[[nodiscard]] auto get_ratio() const -> float;

		~gl_texture();

		static auto from_file(const std::string& path) -> std::shared_ptr<gl_texture>;
		static auto from_surface(SDL_Surface* surface) -> std::shared_ptr<gl_texture>;
	};

}  // namespace sdlk2d