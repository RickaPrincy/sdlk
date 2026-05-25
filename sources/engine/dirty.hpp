//
// Created by ricka on 2026-05-25.
//

#pragma once

namespace sdlk::engine
{
    class dirty_object
    {
        bool m_is_dirty{false};

    public:
        virtual ~dirty_object() = default;

        auto set_dirty(const bool dirty) -> void { m_is_dirty = dirty; }
        auto clear_dirty() -> void { m_is_dirty = false; }
        [[nodiscard]] auto is_dirty() const -> bool { return m_is_dirty; }
    };
}