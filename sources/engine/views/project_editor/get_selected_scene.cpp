//
// Created by ricka on 2026-05-26.
//

#include "components.hpp"

namespace sdlk::engine::editor
{
    auto get_selected_scene(const context_getter& context_getter) -> std::shared_ptr<scene>
    {
        const auto selected_item =  get_selected_item(context_getter);
        if (!selected_item.has_value())
        {
            return nullptr;
        }
        auto selected_item_value = selected_item.value();
        if (selected_item_value.type() != typeid(std::shared_ptr<scene>))
        {
            return nullptr;
        }

        return std::any_cast<std::shared_ptr<scene>>(selected_item_value);
    }
}