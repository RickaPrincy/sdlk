//
// Created by ricka on 2026-05-25.
//

#pragma once

#include <string>

namespace sdlk::engine
{
    struct project;

    class project_serializer
    {
    public:
        static auto serialize(const project& to_serialize) -> void;
        [[nodiscard]] static auto deserialize(const std::string& path) -> project;

        project_serializer() = delete;
    };
}