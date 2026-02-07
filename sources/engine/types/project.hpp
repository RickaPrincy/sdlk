//
// Created by ricka on 2026-02-06.
//

#pragma once

#include <memory>
#include <sdlk/core/components/2d/shape/texture.hpp>
#include <string>

namespace sdlk
{
	class project
	{
		std::shared_ptr<sdlk2d::texture> _texture{};

	protected:
		std::string m_name{};
		std::string m_image_path{};

	public:
		explicit project(std::string name, const std::string &image_path);

		auto open() -> void;
		[[nodiscard]] auto get_name() -> std::string;
		[[nodiscard]] auto get_texture() -> std::shared_ptr<sdlk2d::texture>;

		virtual ~project() = default;
	};
}  // namespace sdlk
