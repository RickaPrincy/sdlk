//
// Created by ricka on 2026-05-25.
//

#pragma once

namespace sdlk::engine
{
    struct project;

    class project_loader
    {
    public:
        static auto load(project to_load) -> void;

        project_loader() = delete;
    };
}
