//
// Created by ricka on 2026-05-25.
//

#include "scene.hpp"

#include <utility>

namespace sdlk::engine
{
    scene::scene(std::string name, const glm::vec2 &canva_size)
    : m_name(std::move(name))
    {
        this->m_raw_scene = std::make_shared<game::scene>(canva_size);
    }

    scene::scene(const std::string &name, const std::shared_ptr<game::scene> &raw_scene)
    {
        this->m_name = name;
        this->m_raw_scene = raw_scene;
    }

    auto scene::get_name() const -> std::string
    {
        return this->m_name;
    }

    auto scene::get_raw_scene() const -> std::shared_ptr<game::scene>
    {
        return this->m_raw_scene;
    }
}
