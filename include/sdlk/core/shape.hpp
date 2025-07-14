#pragma once

#include <SDL2/SDL_pixels.h>
#include <glad/glad.h>

#include <memory>
#include <sdlk/core/freetype_font.hpp>
#include <sdlk/core/renderable.hpp>
#include <sdlk/core/texture.hpp>
#include <sdlk/core/types.hpp>
#include <vector>

namespace sdlk
{
	class shape : public renderable
	{
	protected:
		polygon m_polygon{};
		bool m_use_texture{ false };
		unsigned int m_indices_count{};

		GLuint m_vao{}, m_vbo{}, m_ebo{};

		shape(polygon polygon, std::vector<uint32_t> indices, bool use_texture = false);

	public:
		virtual auto bind() -> void const;

		virtual auto render(GLuint *program) -> void override;

		virtual ~shape();
	};

	class text_shape : public shape
	{
	protected:
		std::string m_text{};
		std::shared_ptr<freetype_font> m_font = nullptr;

	public:
		[[nodiscard]] auto get_text() -> std::string;

		virtual auto bind() -> void const override;
		virtual auto render(GLuint *program) -> void override;

		text_shape(std::string text, std::shared_ptr<freetype_font> font);
		~text_shape() = default;
	};

	class colored_shape : public shape
	{
	public:
		colored_shape(polygon geometry, std::vector<SDL_Color> color);
		colored_shape(polygon geometry,
			std::vector<SDL_Color> colors,
			std::vector<uint32_t> indices);

		colored_shape(polygon geometry, SDL_Color color);
		colored_shape(polygon geometry, SDL_Color color, std::vector<uint32_t> indices);

		virtual ~colored_shape() = default;
	};

	class textured_shape : public shape
	{
	protected:
		std::shared_ptr<texture> m_texture = nullptr;

	public:
		textured_shape(polygon geometry, std::vector<point> uv, std::shared_ptr<texture> texture);
		textured_shape(polygon geometry,
			std::vector<point> uv,
			std::shared_ptr<texture> texture,
			std::vector<uint32_t> indices);

		virtual auto render(GLuint *program) -> void override;
		virtual auto bind() -> const void override;

		virtual ~textured_shape() = default;
	};

	class image_shape : public textured_shape
	{
	public:
		image_shape(std::string path, int width, int height);

		virtual ~image_shape() = default;
	};
}  // namespace sdlk
