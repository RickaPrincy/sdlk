//
// Created by ricka on 2026-01-18.
//

#include <sdlk/core/fonts/msdf_font.hpp>
#include <stdexcept>

#include "free_type_handle_wrapper.hpp"

namespace sdlk
{
	msdf_font::msdf_font(std::string font_path, msdf_font_conf&& conf)
		: m_conf(conf),
		  m_font_path(std::move(font_path))
	{
		this->m_font_handle =
			msdfgen::loadFont(free_type_handle_wrapper::instance()->raw(), m_font_path.c_str());

		if (!this->m_font_handle)
		{
			throw std::runtime_error("Could not load font " + m_font_path);
		}
	}

	msdf_font::~msdf_font()
	{
		msdfgen::destroyFont(this->m_font_handle);
	}

	auto msdf_font::make(std::string font_path) -> std::shared_ptr<msdf_font>
	{
		return std::make_shared<msdf_font>(std::move(font_path));
	}
}  // namespace sdlk