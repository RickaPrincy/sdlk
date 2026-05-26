//
// Created by ricka on 2026-05-20.
//

#include "../../types/project.hpp"
#include "../../utils/nfd_wrapper.hpp"
#include "../../loader/project_loader.hpp"
#include "../../serializer/project_serializer.hpp"

namespace sdlk::engine::home_view
{
    auto trigger_open_project() -> void
    {
        if (const auto response = nfd_wrapper::instance().open_folder_dialog();
            response.m_type == nfd_open_dialog_result::type::success)
        {
            const auto path = response.m_path;
            const auto to_open = project_serializer::deserialize(path.value());
            project_loader::load(to_open);
        }
    }
}
