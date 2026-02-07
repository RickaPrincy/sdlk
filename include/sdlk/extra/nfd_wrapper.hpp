//
// Created by ricka on 2026-02-07.
//

#pragma once

#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace sdlk
{
	struct nfd_filter
	{
		std::string m_name{};
		std::string m_extensions{};
	};

	struct nfd_open_dialog_result
	{
		enum class type
		{
			canceled,
			success,
			error
		};

		type m_type{ type::canceled };
		std::optional<std::string> m_path{};

		explicit nfd_open_dialog_result(type type,
			const std::optional<std::string> &path = std::nullopt)
		{
			this->m_path = path;
			this->m_type = type;
		}
	};

	class nfd_wrapper
	{
	public:
		explicit nfd_wrapper();

		virtual ~nfd_wrapper();

		[[nodiscard]] static auto instance() -> std::shared_ptr<nfd_wrapper>;
		[[nodiscard]] auto open_file_dialog(const std::vector<nfd_filter> &filters)
			-> nfd_open_dialog_result;
	};
}  // namespace sdlk
