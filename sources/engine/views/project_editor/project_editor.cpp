//
// Created by ricka on 2026-05-17.
//

#include "../view.hpp"
#include <imgui.h>
#include <sdlk/core/imgui/imgui_renderable.hpp>

static int selected_entity_id = 0;
static int selected_scene_id = 0;

static const char* scenes[] = { "level_01_sandbox", "level_02_forest", "main_menu_scene", "intro_cinematic" };

static auto inject_premium_dark_theme() -> void
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

static auto draw_scene_list_manager() -> void
{
    ImGui::TextDisabled("ALL SCENES IN PROJECT");
    ImGui::Dummy(ImVec2(0.0f, 4.0f));

    for (int i = 0; i < IM_ARRAYSIZE(scenes); i++)
    {
        ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
        if (selected_scene_id == i) flags |= ImGuiTreeNodeFlags_Selected;

        ImGui::TreeNodeEx(reinterpret_cast<void *>(static_cast<intptr_t>(i)), flags, "  %s.scene", scenes[i]);
        if (ImGui::IsItemClicked())
        {
            selected_scene_id = i;
        }
    }
}

static auto draw_scene_hierarchy() -> void
{
    ImGui::TextDisabled("ACTIVE REGISTRY ENTITIES");
    ImGui::Dummy(ImVec2(0.0f, 4.0f));

    if (ImGui::Selectable("  Entity_01 (Player)", selected_entity_id == 0)) selected_entity_id = 0;
    if (ImGui::Selectable("  Entity_02 (Main_Camera)", selected_entity_id == 1)) selected_entity_id = 1;
    if (ImGui::Selectable("  Entity_03 (Background_Quad)", selected_entity_id == 2)) selected_entity_id = 2;
    if (ImGui::Selectable("  Entity_04 (Enemy_Spawner)", selected_entity_id == 3)) selected_entity_id = 3;
}

static auto draw_left_sidebar_tabs() -> void
{
    ImGui::BeginChild("LeftSidebarPanel", ImVec2(0, 0), true);
    if (ImGui::BeginTabBar("LeftPanelTabBar"))
    {
        if (ImGui::BeginTabItem("Hierarchy & Scenes"))
        {
            ImGui::Dummy(ImVec2(0.0f, 6.0f));
            draw_scene_hierarchy();

            ImGui::Dummy(ImVec2(0.0f, 12.0f));
            ImGui::Separator();
            ImGui::Dummy(ImVec2(0.0f, 12.0f));

            draw_scene_list_manager();
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Scene Config"))
        {
            ImGui::Dummy(ImVec2(0.0f, 8.0f));
            ImGui::Text("Active Target: %s", scenes[selected_scene_id]);
            ImGui::Dummy(ImVec2(0.0f, 4.0f));
            ImGui::Separator();
            ImGui::Dummy(ImVec2(0.0f, 8.0f));

            static char scene_name[64] = "level_01_sandbox";
            ImGui::InputText("Name", scene_name, IM_ARRAYSIZE(scene_name));

            static float ambient_color[4] = { 0.1f, 0.1f, 0.15f, 1.0f };
            ImGui::ColorEdit4("Clear Color", ambient_color);

            static int max_entities = 5000;
            ImGui::InputInt("ECS Limit", &max_entities);

            ImGui::Dummy(ImVec2(0.0f, 12.0f));
            if (ImGui::Button("Clear Current Registry", ImVec2(-1, 24))) {}
            if (ImGui::Button("Instantiate Prefab Blueprint...", ImVec2(-1, 24))) {}
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }
    ImGui::EndChild();
}

static auto draw_project_browser() -> void
{
    ImGui::BeginChild("ProjectBrowserPanel", ImVec2(0, 0), true);
    if (ImGui::BeginTabBar("ProjectTabs"))
    {
        if (ImGui::BeginTabItem("Assets (Disk)"))
        {
            ImGui::Dummy(ImVec2(0.0f, 6.0f));
            if (ImGui::TreeNodeEx("assets/", ImGuiTreeNodeFlags_DefaultOpen))
            {
                if (ImGui::TreeNode("textures/"))
                {
                    ImGui::Selectable("player_sheet.png");
                    ImGui::Selectable("background.png");
                    ImGui::TreePop();
                }
                if (ImGui::TreeNode("meshes/"))
                {
                    ImGui::Selectable("cube.obj");
                    ImGui::Selectable("quad_mesh.json");
                    ImGui::TreePop();
                }
                if (ImGui::TreeNode("fonts/"))
                {
                    ImGui::Selectable("arial_msdf.png");
                    ImGui::TreePop();
                }
                ImGui::TreePop();
            }
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Active GPU Resources"))
        {
            ImGui::Dummy(ImVec2(0.0f, 6.0f));
            if (ImGui::CollapsingHeader("Loaded Textures (gl_texture)", ImGuiTreeNodeFlags_DefaultOpen))
            {
                ImGui::Text("ID: 1 | player_sheet [Slot 0]");
                ImGui::Text("ID: 2 | background   [Slot 1]");
            }
            if (ImGui::CollapsingHeader("Compiled Geometries (geometry)", ImGuiTreeNodeFlags_DefaultOpen))
            {
                ImGui::Text("ID: 1 | default_quad_mesh [Indexed]");
                ImGui::Text("ID: 2 | player_hitbox_poly [Non-Indexed]");
            }
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }
    ImGui::EndChild();
}

static auto draw_entity_inspector() -> void
{
    ImGui::BeginChild("InspectorPanel", ImVec2(0, 0), true);
    if (selected_entity_id != -1)
    {
        ImGui::Text("Entity Object ID: %d", selected_entity_id);
        ImGui::Dummy(ImVec2(0.0f, 4.0f));
        ImGui::Separator();
        ImGui::Dummy(ImVec2(0.0f, 6.0f));

        if (ImGui::CollapsingHeader("sdlk::game::transform", ImGuiTreeNodeFlags_DefaultOpen))
        {
            static float pos[3] = { 0.0f, 0.0f, 0.0f };
            static float rot[3] = { 0.0f, 0.0f, 0.0f };
            static float scale[3] = { 1.0f, 1.0f, 1.0f };

            ImGui::Dummy(ImVec2(0.0f, 4.0f));
            ImGui::DragFloat3("Position", pos, 0.05f);
            ImGui::DragFloat3("Rotation", rot, 0.5f, 0.0f, 360.0f);
            ImGui::DragFloat3("Scale", scale, 0.01f, 0.01f, 100.0f);
            ImGui::Dummy(ImVec2(0.0f, 6.0f));
        }

        if (selected_entity_id != 1 && selected_entity_id != 3)
        {
            if (ImGui::CollapsingHeader("sdlk::game::mesh", ImGuiTreeNodeFlags_DefaultOpen))
            {
                ImGui::Dummy(ImVec2(0.0f, 4.0f));
                ImGui::Text("Resource Pointer: 0x7FFF90B2");
                ImGui::Text("Active VAO Handle: 4");
                ImGui::Text("Primitive Layout: GL_TRIANGLES");
                ImGui::Dummy(ImVec2(0.0f, 6.0f));
            }
        }

        if (selected_entity_id == 0 || selected_entity_id == 2)
        {
            if (ImGui::CollapsingHeader("sdlk::game::texture", ImGuiTreeNodeFlags_DefaultOpen))
            {
                static float uv_offset[2] = { 0.0f, 0.0f };
                ImGui::Dummy(ImVec2(0.0f, 4.0f));
                ImGui::DragFloat2("UV Offset", uv_offset, 0.005f);
                ImGui::Text("OpenGL Texture ID: 12");
                ImGui::Text("Size: 512x512 px");
                ImGui::Dummy(ImVec2(0.0f, 6.0f));
            }
        }

        if (selected_entity_id == 0)
        {
            if (ImGui::CollapsingHeader("sdlk::game::velocity", ImGuiTreeNodeFlags_DefaultOpen))
            {
                static float vel[3] = { 5.0f, 0.0f, 0.0f };
                ImGui::Dummy(ImVec2(0.0f, 4.0f));
                ImGui::InputFloat3("Linear Velocity", vel, "%.3f");
                ImGui::Dummy(ImVec2(0.0f, 6.0f));
            }
        }

        ImGui::Dummy(ImVec2(0.0f, 12.0f));
        ImGui::Separator();
        ImGui::Dummy(ImVec2(0.0f, 6.0f));

        if (ImGui::Button("Add Component", ImVec2(-1, 26)))
        {
            ImGui::OpenPopup("AddComponentPopup");
        }

        if (ImGui::BeginPopup("AddComponentPopup"))
        {
            if (ImGui::MenuItem("sdlk::game::velocity")) {}
            if (ImGui::MenuItem("sdlk::game::texture")) {}
            if (ImGui::MenuItem("sdlk::game::mesh")) {}
            ImGui::EndPopup();
        }
    }
    ImGui::EndChild();
}

static auto draw_game_viewport() -> void
{
    ImGui::BeginChild("ViewportPanel", ImVec2(0, 0), true);
    ImVec2 size = ImGui::GetContentRegionAvail();
    ImGui::TextDisabled("SCENE DRAW SPACE");
    ImGui::Text("Dimensions: %.0fx%.0f px", size.x, size.y);
    ImGui::EndChild();
}

static auto draw_editor_panels() -> std::function<void()>
{
    return []() {
        inject_premium_dark_theme();

        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar;
        const ImGuiViewport* viewport = ImGui::GetMainViewport();

        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

        ImGui::Begin("SDLK Engine Editor Workspace", nullptr, window_flags);

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                ImGui::MenuItem("New Project");
                ImGui::MenuItem("Exit");
                ImGui::EndMenu();
            }

            ImGui::Separator();

            if (ImGui::MenuItem("Save Project")) {}

            ImGui::Separator();

            if (ImGui::MenuItem("New Scene")) {}

            ImGui::Separator();

            ImGui::SetNextItemWidth(140);
            if (ImGui::BeginCombo("##TopMenuSceneCombo", scenes[selected_scene_id], ImGuiComboFlags_HeightLarge))
            {
                for (int i = 0; i < IM_ARRAYSIZE(scenes); i++)
                {
                    if (ImGui::Selectable(scenes[i], selected_scene_id == i)) selected_scene_id = i;
                }
                ImGui::EndCombo();
            }

            ImGui::Separator();

            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.14f, 0.34f, 0.14f, 1.0f));
            if (ImGui::Button("Play", ImVec2(45, 0))) {}
            ImGui::PopStyleColor();

            ImGui::SameLine();
            if (ImGui::Button("Pause", ImVec2(45, 0))) {}

            ImGui::EndMenuBar();
        }

        ImGui::Dummy(ImVec2(0.0f, 2.0f));

        ImGui::Columns(3, "EditorLayoutColumns", true);

        static bool initial_widths_set = false;
        if (!initial_widths_set)
        {
            ImGui::SetColumnWidth(0, viewport->WorkSize.x * 0.20f);
            ImGui::SetColumnWidth(1, viewport->WorkSize.x * 0.56f);
            ImGui::SetColumnWidth(2, viewport->WorkSize.x * 0.24f);
            initial_widths_set = true;
        }

        ImGui::BeginGroup();
        ImVec2 av_size = ImGui::GetContentRegionAvail();
        ImGui::BeginChild("LeftGroupWrapper", ImVec2(0, av_size.y * 0.52f), false);
        draw_left_sidebar_tabs();
        ImGui::EndChild();
        ImGui::Dummy(ImVec2(0.0f, 4.0f));
        draw_project_browser();
        ImGui::EndGroup();

        ImGui::NextColumn();

        draw_game_viewport();

        ImGui::NextColumn();

        draw_entity_inspector();

        ImGui::Columns(1);
        ImGui::End();
    };
}

auto sdlk::project_editor() -> std::shared_ptr<component>
{
    auto project_view = std::make_shared<component>();
    project_view->add_child(imgui_renderable::make(draw_editor_panels()));
    return project_view;
}