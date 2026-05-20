//
// Created by ricka on 2026-05-20.
//

#include <sdlk/extra/nfd_wrapper.hpp>
#include "../../types/project.hpp"

namespace sdlk
{
    auto trigger_open_project() -> void
    {
        if (const auto response = nfd_wrapper::instance()->open_folder_dialog();
            response.m_type == nfd_open_dialog_result::type::success)
        {
            auto path = response.m_path;
            const auto to_open = std::make_shared<project>(path.value());

            to_open->open();
        }
    }
}
