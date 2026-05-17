//
// Created by ricka on 2026-02-06.
//

#include <imgui.h>

#include <sdlk/core/imgui/imgui_drawer_utils.hpp>
#include <sdlk/core/imgui/imgui_renderable.hpp>
#include <sdlk/extra/nfd_wrapper.hpp>

#include "components.hpp"
#include "../view.hpp"
#include "../../types/project.hpp"
#include "../../conf/sdlk_engine_conf.hpp"

namespace sdlk
{
	static auto draw_home_content() -> void;
	static auto open_existing_project() -> void;
    static auto get_last_projects() -> std::vector<std::shared_ptr<project>>;

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
				ImGui::Begin("Welcome to SDLK Game Creator",
					nullptr,
					ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
						ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);

				const float content_width = ImGui::GetContentRegionAvail().x;

				imgui_drawer_utils::image(logo, ImVec2{ content_width, 300.0F });
				imgui_drawer_utils::spacing(2);

				ImGui::Button("Create a new Project", ImVec2(content_width, 0));

				imgui_drawer_utils::spacing();

				if (ImGui::Button("Open a Project", ImVec2(content_width, 0)))
				{
					open_existing_project();
				}

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

	auto open_existing_project() -> void
	{
		if (const auto response = nfd_wrapper::instance()->open_folder_dialog();
			response.m_type == nfd_open_dialog_result::type::success)
		{
		    auto path = response.m_path;
		    const auto to_open = std::make_shared<project>(path.value());

		    to_open->open();
		}
	}

    auto get_last_projects() -> std::vector<std::shared_ptr<project>>
    {
        std::vector<std::shared_ptr<project>> projects{};

	    projects.reserve(sdlk_engine_conf::MAX_RECENTS);
	    const auto last_project_paths = sdlk_engine_conf::load_or_init()->get_last_project_paths();
	    for (const auto& path : last_project_paths)
	    {
	        projects.emplace_back(std::make_shared<project>(path));
	    }
	    return projects;
    }
}  // namespace sdlk