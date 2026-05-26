//
// Created by ricka on 2026-05-26.
//

#include "components.hpp"

namespace sdlk::engine::editor
{
    auto get_selected_item(const context_getter &context_getter) -> std::optional<std::any>
    {
        const auto &props = context_getter();
        const auto it = props.find("selected_item");
        if (it == props.end())
        {
            return std::nullopt;
        }

        return it->second;
    }
}