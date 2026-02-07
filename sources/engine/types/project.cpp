//
// Created by ricka on 2026-02-06.
//

#include "project.hpp"

#include <stdexcept>
#include <utility>

namespace sdlk
{
	project::project(std::string name, const std::string& image_path)
		: _texture(gl_texture::from_file(image_path)),
		  m_name(std::move(name)),
		  m_image_path(image_path)
	{
	}

	auto project::open() -> void
	{
		throw std::runtime_error("Not implemented");
	}

	auto project::get_texture() -> std::shared_ptr<gl_texture>
	{
		return this->_texture;
	}

	auto project::get_name() -> std::string
	{
		return this->m_name;
	}
}  // namespace sdlk