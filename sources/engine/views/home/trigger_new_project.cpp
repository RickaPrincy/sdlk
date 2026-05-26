//
// Created by ricka on 2026-05-20.
//

#include <string>
#include <Templi/Templi.hpp>

#include "../../types/project.hpp"
#include "../../utils/utils.hpp"
#include "../../sdlk_engine_conf.hpp"
#include "../../loader/project_loader.hpp"
#include "../../serializer/project_serializer.hpp"

#define GAME_NAME_PLACEHOLDER_NAME "GAME_NAME"

namespace sdlk::engine::home_view
{
     auto trigger_new_project(const std::string &path, const std::string &name) -> void
     {
         auto game_name = utils::sanitize(name);
         const auto output_path = std::filesystem::path(path) / game_name;
         const auto template_path = sdlk_engine_conf::get_template_path();

         Templi::generate_with_templi_config(
             template_path,
             output_path,
             [game_name](const Templi::Placeholder &placeholder)
             {
                 if (placeholder.m_name == std::string(GAME_NAME_PLACEHOLDER_NAME))
                 {
                     return game_name;
                 }
                 throw std::runtime_error("Placeholder not found: " + placeholder.m_name);
            });

         const project created{
             .m_path=output_path.string(),
             .m_name=game_name
         };
         project_serializer::serialize(created);
         sdlk_engine_conf::load_or_init()->add_recent_project(created.m_path);
         project_loader::load(created);
     }
}
