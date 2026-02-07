//
// Created by ricka on 2026-02-06.
//

#include <memory>
#include <sdlk/core/imgui/imgui_drawer_utils.hpp>

namespace sdlk::imgui_drawer_utils
{
	auto centered_window(const std::function<ImVec2()>& size_getter,
		const std::function<void()>& renderable) -> void
	{
		const auto size = size_getter();
		const ImGuiViewport* vp = ImGui::GetMainViewport();
		const ImVec2 pos(
			vp->Pos.x + (vp->Size.x - size.x) * 0.5f, vp->Pos.y + (vp->Size.y - size.y) * 0.5f);

		ImGui::SetNextWindowPos(pos, ImGuiCond_Always);
		ImGui::SetNextWindowSize(size, ImGuiCond_Always);

		renderable();
	}

	auto image(const std::shared_ptr<gl_texture>& texture, const ImVec2& size) -> void
	{
		ImGui::Image(static_cast<ImTextureID>(static_cast<intptr_t>(texture->get_id())), size);
	}

	auto spacing(const int iteration) -> void
	{
		for (int i = 0; i < iteration; ++i)
		{
			ImGui::Spacing();
		}
	}
}  // namespace sdlk::imgui_drawer_utils