//
// Created by ricka on 2026-01-24.
//

#pragma once

#include <memory>
#include <sdlk/core/color.hpp>
#include <sdlk/core/renderable.hpp>
#include <sdlk/core/2d/fonts/msdf_font.hpp>
#include <string>

namespace sdlk2d
{
    struct text_style
    {
        float m_size{ 12.0f };
        sdlk::color m_fg_color{ sdlk::color::white() };
        sdlk::color m_bg_color{ SDL_Color{ .r = 0, .g = 0, .b = 0, .a = 0 } };
    };

	struct char_vertex
	{
		glm::vec3 m_pos;
		glm::vec2 m_uv;
	};

	class text_shape : public sdlk::renderable
	{
		std::vector<char_vertex> m_vertices{};

	protected:
		text_style m_style{};
		std::u32string m_text{};
		std::shared_ptr<msdf_font> m_font{};

		auto update_vertices() -> void;

	public:
		explicit text_shape(std::u32string text,
			const text_style &text_style,
			const std::shared_ptr<msdf_font> &font);

		auto render(const std::shared_ptr<sdlk::gl_program> &program) -> void override;
	};
}  // namespace sdlk2d