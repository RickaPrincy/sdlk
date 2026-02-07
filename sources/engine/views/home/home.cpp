//
// Created by ricka on 2026-02-06.
//

#include <sdlk/core/imgui/imgui_drawer_utils.hpp>
#include <sdlk/core/imgui/imgui_renderable.hpp>

#include "../../types/project.hpp"
#include "../view.hpp"
#include "components.hpp"
#include "imgui.h"

namespace sdlk
{
	auto draw_home_content() -> void;

	auto home() -> std::shared_ptr<component>
	{
		auto home_view = std::make_shared<component>();
		home_view->add_child(imgui_renderable::make(&draw_home_content));
		return home_view;
	}

	auto draw_home_content() -> void
	{
		static const std::shared_ptr<sdlk2d::texture> logo =
			sdlk2d::texture::from_file("./resources/images/sdlk.png");

		static const std::vector projects{ std::make_shared<project>(
											   "Alpha", "./resources/images/examples/game_bg.png"),
			std::make_shared<project>("Beta", "./resources/images/examples/game_bg.png"),
			std::make_shared<project>("Mario Kart", "./resources/images/examples/game_bg.png") };

		imgui_drawer_utils::centered_window(
			[]
			{
				const ImGuiViewport* vp = ImGui::GetMainViewport();
				return ImVec2(vp->Size.x * 0.7f, vp->Size.y * 0.75f);
			},
			[]
			{
				ImGui::Begin("Welcome to SDLK Game Creator",
					nullptr,
					ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
						ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);

				const float content_width = ImGui::GetContentRegionAvail().x;

				imgui_drawer_utils::image(logo, ImVec2{ content_width, 250.0F });
				imgui_drawer_utils::spacing(2);

				ImGui::Button("Create a new Project", ImVec2(content_width, 0));

				imgui_drawer_utils::spacing();

				ImGui::Button("Open a Project", ImVec2(content_width, 0));

				imgui_drawer_utils::spacing();
				ImGui::Separator();
				imgui_drawer_utils::spacing();

				ImGui::Text("Last Projects");
				imgui_drawer_utils::spacing();

				constexpr float padding = 8.0f;
				constexpr float card_size = 140.0f;
				const float available_width = content_width;
				int times_per_row = static_cast<int>(available_width / (card_size + padding));

				if (times_per_row < 1)
				{
					times_per_row = 1;
				}

				for (int i = 0; i < projects.size(); ++i)
				{
					if (i != 0 && i % times_per_row != 0)
					{
						ImGui::SameLine(0, padding);
					}
					draw_project_card(projects[i]);
				}

				ImGui::End();
			});
	}

}  // namespace sdlk