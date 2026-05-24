//
// Created by ricka on 2026-05-24.
//

#include <sdlk/game/systems/render_system.hpp>

#include <sdlk/game/components/mesh.hpp>
#include <sdlk/game/components/texture.hpp>

namespace sdlk::game
{
    auto render_system::update(world &world, const std::shared_ptr<gl_program> &program) -> void
    {
        auto &meshes = world.pool<mesh>();
        auto &textures = world.pool<texture>();
        const auto &uniform = program->get_uniform();

        uniform->set("u_text_rendering", false);
        uniform->set("u_use_vertex_color", false);

        for (const auto &e : meshes.get_entities())
        {
            const auto has_texture = textures.has(e);
            uniform->set("u_use_texture", has_texture);

            if (has_texture)
            {
                const auto &[m_uv_offset, m_texture] = textures.get(e);
                m_texture->bind();
                uniform->set("u_texture", 0);
            }

            auto &[m_shape] = meshes.get(e);
            m_shape->render(program);
        }
    }
}
