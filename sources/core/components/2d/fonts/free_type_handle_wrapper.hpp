//
// Created by ricka on 2026-01-18.
//
#pragma once

#include <msdf-atlas-gen/msdf-atlas-gen.h>

namespace sdlk
{
	class free_type_handle_wrapper final
	{
		msdfgen::FreetypeHandle *_ft_handle{ nullptr };

	public:
		free_type_handle_wrapper();

		[[nodiscard]] auto raw() const -> msdfgen::FreetypeHandle *;

		[[nodiscard]] static auto instance() -> free_type_handle_wrapper *;

		~free_type_handle_wrapper();
	};
}  // namespace sdlk