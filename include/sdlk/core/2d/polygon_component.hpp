//
// Created by ricka on 2026-05-24.
//

#pragma once

#include <sdlk/core/color.hpp>
#include <sdlk/core/transform.hpp>
#include <sdlk/core/gl/gl_texture.hpp>
#include <sdlk/core/2d/shape/polygon_shape.hpp>
#include <sdlk/core/component.hpp>

namespace sdlk2d
{
    struct polygon_component_style
    {
        enum class type
        {
            uniform,
            vertex,
            texture,
        };

        type m_type{ type::uniform };
        std::shared_ptr<sdlk::gl_texture> m_texture{};
        std::optional<sdlk::color> m_uniform_color{};

        explicit polygon_component_style()
        {
            this->m_type = type::vertex;
        }

        explicit polygon_component_style(const sdlk::color &color)
        {
            this->m_type = type::uniform;
            this->m_uniform_color = color;
        }

        explicit polygon_component_style(const std::shared_ptr<sdlk::gl_texture> &texture)
        {
            this->m_type = type::texture;
            this->m_texture = texture;
        }
    };

    class polygon_component: public sdlk::component
    {
    protected:
        sdlk::transform m_transform{};
        polygon_component_style m_style{};

    public:
		explicit polygon_component(std::shared_ptr<polygon_shape> shape, polygon_component_style style, const
		    std::vector<std::shared_ptr<renderable>> &childs = {});

        auto render(const std::shared_ptr<sdlk::gl_program> &program) -> void override;
    };
}
