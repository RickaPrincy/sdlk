//
// Created by ricka on 2026-02-06.
//

#include <sdlk/core/imgui/imgui_drawer_utils.hpp>

#include "components.hpp"
#include "imgui.h"

namespace sdlk
{
	static constexpr ImVec2 CARD_SIZE{ 200, 200 };

	auto draw_project_card(const std::shared_ptr<project>& project) -> void
	{
		ImGui::BeginGroup();
		imgui_drawer_utils::image(project->get_texture(), CARD_SIZE);
		ImGui::Text("%s", project->get_name().c_str());
		ImGui::EndGroup();
	}
}  // namespace sdlk
