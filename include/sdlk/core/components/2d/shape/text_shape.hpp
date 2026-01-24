//
// Created by ricka on 2026-01-24.
//

#pragma once

#include <memory>
#include <sdlk/core/fonts/msdf_font.hpp>
#include <sdlk/core/renderable/renderable.hpp>
#include <string>

namespace sdlk2d
{
	class text_shape : public sdlk::renderable
	{
		std::string m_text{};
		std::shared_ptr<sdlk::msdf_font> m_font{};

	public:
		explicit text_shape(std::string text, const std::shared_ptr<sdlk::msdf_font> &font);

		auto render(const std::shared_ptr<sdlk::gl_program> &program) -> void override;
	};
}  // namespace sdlk2d