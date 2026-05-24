//
// Created by ricka on 2026-05-21.
//

#pragma once

#include <memory>
#include <sdlk/core/app.hpp>
#include <sdlk/game/game_view.hpp>

namespace sdlk::game
{
    class game: public app
    {
        std::shared_ptr<game_view> m_game_view;

        auto run(const std::string &default_view, int argc, char **argv) -> int override;
    public:
        auto run(int argc, char ** argv) -> int;

        game(const std::string &window_title,
            const int &width,
            const int &height,
            const app_options &options = {},
            Uint32 sdl_init_flags = SDL_INIT_EVERYTHING);

        game() = delete;
        ~game() override = default;
    };
}
