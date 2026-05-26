//
// Created by ricka on 2026-05-25.
//

#pragma once

#include <string>
#include <sdlk/game/scenes/scene.hpp>

namespace sdlk::engine
{
    class scene
    {
        std::string m_name{};
        std::shared_ptr<game::scene> m_raw_scene{};

    public:
        explicit scene(std::string name, const glm::vec2& canva_size);
        explicit scene(const std::string &name, const std::shared_ptr<game::scene> &raw_scene);

        [[nodiscard]] auto get_name() const -> std::string;
        [[nodiscard]] auto get_raw_scene() const -> std::shared_ptr<game::scene>;
    };
}
