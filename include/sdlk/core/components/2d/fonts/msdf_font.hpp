//
// Created by ricka on 2026-05-18.
//

#pragma once

#include <memory>
#include <string>

namespace sdlk2d
{
    class msdf_font_impl;

    struct msdf_font_conf
    {
        const float m_pixel_range = 2;
        const float m_glyph_scale = 32.0;
        const float m_miter_limit = 1.0;
        const float m_max_corner_angle = 3.0;
    };

    class msdf_font
    {
        msdf_font_conf m_conf;
        std::shared_ptr<msdf_font_impl> m_impl;

    public:
        explicit msdf_font(const std::string &path, msdf_font_conf conf = {});

        [[nodiscard]] auto get_impl() const -> std::shared_ptr<msdf_font_impl>;

        [[nodiscard]] static auto make(const std::string &path, msdf_font_conf conf = {}) -> std::shared_ptr<msdf_font>;

        msdf_font() = delete;
        ~msdf_font() = default;
    };
}
