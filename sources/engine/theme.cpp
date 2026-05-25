//
// Created by ricka on 2026-05-25.
//

#include <imgui.h>
#include "theme.hpp"

auto sdlk::engine::configure_theme() -> void
{
    ImGuiStyle& style = ImGui::GetStyle();

    style.WindowPadding = ImVec2(6.0f, 6.0f);
    style.FramePadding = ImVec2(5.0f, 4.0f);
    style.ItemSpacing = ImVec2(6.0f, 6.0f);
    style.ItemInnerSpacing = ImVec2(6.0f, 4.0f);
    style.ScrollbarSize = 13.0f;
    style.WindowBorderSize = 1.0f;
    style.ChildBorderSize = 1.0f;
    style.PopupBorderSize = 1.0f;
    style.FrameBorderSize = 1.0f;
    style.TabBorderSize = 1.0f;

    style.WindowRounding = 0.0f;
    style.ChildRounding = 4.0f;
    style.FrameRounding = 3.0f;
    style.PopupRounding = 4.0f;
    style.ScrollbarRounding = 4.0f;
    style.TabRounding = 3.0f;

    ImVec4* colors = style.Colors;
    colors[ImGuiCol_Text]                   = ImVec4(0.88f, 0.90f, 0.93f, 1.00f);
    colors[ImGuiCol_TextDisabled]           = ImVec4(0.48f, 0.51f, 0.56f, 1.00f);
    colors[ImGuiCol_WindowBg]               = ImVec4(0.09f, 0.09f, 0.10f, 1.00f);
    colors[ImGuiCol_ChildBg]                = ImVec4(0.12f, 0.13f, 0.14f, 1.00f);
    colors[ImGuiCol_PopupBg]                = ImVec4(0.14f, 0.15f, 0.17f, 1.00f);
    colors[ImGuiCol_Border]                 = ImVec4(0.20f, 0.21f, 0.23f, 1.00f);
    colors[ImGuiCol_BorderShadow]           = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_FrameBg]                = ImVec4(0.17f, 0.18f, 0.20f, 1.00f);
    colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.22f, 0.24f, 0.26f, 1.00f);
    colors[ImGuiCol_FrameBgActive]          = ImVec4(0.26f, 0.29f, 0.32f, 1.00f);
    colors[ImGuiCol_TitleBg]                = ImVec4(0.09f, 0.09f, 0.10f, 1.00f);
    colors[ImGuiCol_TitleBgActive]          = ImVec4(0.09f, 0.09f, 0.10f, 1.00f);
    colors[ImGuiCol_MenuBarBg]              = ImVec4(0.09f, 0.09f, 0.10f, 1.00f);
    colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.12f, 0.13f, 0.14f, 1.00f);
    colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.25f, 0.27f, 0.29f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.31f, 0.33f, 0.36f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.36f, 0.39f, 0.42f, 1.00f);
    colors[ImGuiCol_CheckMark]              = ImVec4(0.26f, 0.53f, 0.87f, 1.00f);
    colors[ImGuiCol_SliderGrab]             = ImVec4(0.26f, 0.53f, 0.87f, 1.00f);
    colors[ImGuiCol_SliderGrabActive]       = ImVec4(0.36f, 0.63f, 0.97f, 1.00f);
    colors[ImGuiCol_Button]                 = ImVec4(0.18f, 0.19f, 0.21f, 1.00f);
    colors[ImGuiCol_ButtonHovered]          = ImVec4(0.24f, 0.26f, 0.29f, 1.00f);
    colors[ImGuiCol_ButtonActive]           = ImVec4(0.30f, 0.33f, 0.37f, 1.00f);
    colors[ImGuiCol_Header]                 = ImVec4(0.18f, 0.20f, 0.22f, 1.00f);
    colors[ImGuiCol_HeaderHovered]          = ImVec4(0.24f, 0.27f, 0.30f, 1.00f);
    colors[ImGuiCol_HeaderActive]           = ImVec4(0.30f, 0.34f, 0.38f, 1.00f);
    colors[ImGuiCol_Separator]              = ImVec4(0.20f, 0.21f, 0.23f, 1.00f);
    colors[ImGuiCol_Tab]                    = ImVec4(0.12f, 0.13f, 0.14f, 1.00f);
    colors[ImGuiCol_TabHovered]             = ImVec4(0.22f, 0.24f, 0.26f, 1.00f);
    colors[ImGuiCol_TabActive]              = ImVec4(0.17f, 0.18f, 0.20f, 1.00f);
    colors[ImGuiCol_TabUnfocused]           = ImVec4(0.12f, 0.13f, 0.14f, 1.00f);
    colors[ImGuiCol_TabUnfocusedActive]     = ImVec4(0.17f, 0.18f, 0.20f, 1.00f);

    ImGui::GetIO().FontGlobalScale = 0.88f;
}
