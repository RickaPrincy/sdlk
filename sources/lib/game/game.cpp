//
// Created by ricka on 2026-05-21.
//

#include <sdlk/game/game.hpp>
#include <sdlk/game/game_view.hpp>

#define GAME_VIEW_NAME "game"

namespace sdlk::game
{
    game::game(const std::string &window_title,
             const int &width,
             const int &height,
             const app_options &options,
             const Uint32 sdl_init_flags)
        : app(window_title, width, height, options, sdl_init_flags)
    {
        this->m_game_view = std::make_shared<game_view>();
        this->add_view(GAME_VIEW_NAME, this->m_game_view);
    }

    auto game::set_scene(const std::shared_ptr<scene> &scene) const -> void
    {
        auto &scene_manager = this->m_game_view->get_scene_manager();
        scene_manager.change(scene);
    }

    auto game::run(const std::string &default_view, const int argc, char ** argv) -> int
    {
        return this->app::run(GAME_VIEW_NAME, argc, argv);
    }

    auto game::run(const int argc, char **argv) -> int
    {
        return this->app::run(GAME_VIEW_NAME, argc, argv);
    }
}
