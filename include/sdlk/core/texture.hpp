#pragma once

#include <SDL2/SDL_surface.h>
#include <glad/glad.h>

#include <memory>
#include <string>

namespace sdlk
{
	class texture
	{
	private:
		GLuint m_id{ 0 };
		int m_width{}, m_height{};

	public:
		texture(GLuint id, int width, int height);

		auto bind(GLuint unit = 0) const -> void;

		[[nodiscard]] auto get_width() const -> int;
		[[nodiscard]] auto get_height() const -> int;

		~texture();

		static auto from_file(const std::string& path) -> std::shared_ptr<texture>;
		static auto from_surface(SDL_Surface* surface) -> std::shared_ptr<texture>;
	};

}  // namespace sdlk
