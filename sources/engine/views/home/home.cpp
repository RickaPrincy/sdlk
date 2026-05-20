//
// Created by ricka on 2026-02-06.
//

#include <imgui.h>

#include <sdlk/core/components/component.hpp>
#include <sdlk/core/imgui/imgui_drawer_utils.hpp>
#include <sdlk/core/imgui/imgui_renderable.hpp>
#include <sdlk/extra/nfd_wrapper.hpp>

#include "components.hpp"

namespace sdlk
{
	static auto draw_home_content() -> void;

	auto home() -> std::shared_ptr<component>
	{
		auto home_view = std::make_shared<component>();
		home_view->add_child(imgui_renderable::make(&draw_home_content));
		return home_view;
	}

	auto draw_home_content() -> void
	{
	    static const auto projects = get_last_projects();
		static const std::shared_ptr<gl_texture> logo =
			gl_texture::from_file("./resources/images/home.png");

		imgui_drawer_utils::centered_window(
			[]
			{
				const ImGuiViewport* vp = ImGui::GetMainViewport();
				const float width = vp->Size.x * 0.6f;
				const float height = width / logo->get_ratio() + 100 /* TODO */;
				return ImVec2(width, height);
			},
			[]
			{
			    static bool is_creating_new_project = false;
				ImGui::Begin("Welcome to SDLK Game Creator",
					nullptr,
					ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
						ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);

				const float content_width = ImGui::GetContentRegionAvail().x;

				imgui_drawer_utils::image(logo, ImVec2{ content_width, 300.0F });
				imgui_drawer_utils::spacing(2);

			    if (is_creating_new_project)
			    {
			        draw_create_project(content_width, is_creating_new_project);
			    }
			    else
			    {
			        draw_home_options(content_width, is_creating_new_project);
			    }

				ImGui::End();
			});
	}
}  // namespace sdlk