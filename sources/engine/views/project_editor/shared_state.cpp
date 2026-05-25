//
// Created by ricka on 2026-05-25.
//

#include "components.hpp"


namespace sdlk::engine::editor
{
    int selected_scene_idx = -1;
    bool is_playing = false;

    scene_data scenes[3] =
    {
        { "level_01_sandbox", {600, 350} },
        { "level_02_forest",  {700, 400} },
        { "main_menu",         {500, 300} }
    };
}
