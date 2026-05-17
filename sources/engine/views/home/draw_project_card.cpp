//
// Created by ricka on 2026-02-06.
//

#include <imgui.h>
#include "components.hpp"

namespace sdlk
{
	auto draw_project_card(const std::shared_ptr<project>& project) -> void
	{
		ImGui::BeginGroup();
		ImGui::Text("%s", project->get_name().c_str());
		ImGui::EndGroup();
	}
}  // namespace sdlk
