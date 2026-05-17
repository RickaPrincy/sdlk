//
// Created by ricka on 2026-02-06.
//

#pragma once
#include <string>

namespace sdlk
{
	class project
	{
	protected:
		std::string m_name{};
	    std::string m_path{};

	public:
	    explicit project(std::string path);

        auto open() const -> void;
		[[nodiscard]] auto get_name() -> std::string;
	    [[nodiscard]] auto get_path() -> std::string;

		virtual ~project() = default;
	};
}  // namespace sdlk
