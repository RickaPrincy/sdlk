//
// Created by ricka on 2026-05-18.
//

#include <sdlk/core/components/2d/fonts/msdf_font.hpp>
#include "./msdf_font_impl.hpp"

namespace sdlk2d
{
    msdf_font::msdf_font(const std::string &path, const msdf_font_conf conf)
    {
        this->m_impl = std::make_shared<msdf_font_impl>(path, conf);
    }

    auto msdf_font::get_impl() const -> std::shared_ptr<msdf_font_impl>
    {
        return this->m_impl;
    }

    auto msdf_font::make(const std::string &path, msdf_font_conf conf) -> std::shared_ptr<msdf_font>
    {
        return std::make_shared<msdf_font>(path, conf);
    }
}
