//
// Created by ricka on 2025-12-31.
//

#include <glm/gtc/matrix_transform.hpp>
#include <sdlk/core/transform.hpp>

namespace sdlk
{
    auto transform::compose() -> void
    {
       const glm::mat4 T = glm::translate(glm::mat4(1.0f), m_translation);

       auto R = glm::mat4(1.0f);
       R = glm::rotate(R, glm::radians(m_rotation_degrees.y), glm::vec3(0.0f, 1.0f, 0.0f));
       R = glm::rotate(R, glm::radians(m_rotation_degrees.x), glm::vec3(1.0f, 0.0f, 0.0f));
       R = glm::rotate(R, glm::radians(m_rotation_degrees.z), glm::vec3(0.0f, 0.0f, 1.0f));

       const glm::mat4 S = glm::scale(glm::mat4(1.0f), m_scale);
       m_model = T * R * S;
    }

    auto transform::set_translation(const glm::vec3& offset) -> void
    {
       m_translation = offset;
       compose();
    }

    auto transform::set_translation(const glm::vec2& offset) -> void
    {
       m_translation = glm::vec3(offset, 0.0f);
       compose();
    }

    auto transform::add_translation(const glm::vec3& offset) -> void
    {
       m_translation += offset;
       compose();
    }

    auto transform::add_translation(const glm::vec2& offset) -> void
    {
       m_translation += glm::vec3(offset, 0.0f);
       compose();
    }

    auto transform::set_rotation(const glm::vec3& angles_degrees) -> void
    {
       m_rotation_degrees = angles_degrees;
       compose();
    }

    auto transform::set_rotation(const float angle_z_degrees) -> void
    {
       m_rotation_degrees = glm::vec3(0.0f, 0.0f, angle_z_degrees);
       compose();
    }

    auto transform::add_rotation(const glm::vec3& angles_degrees) -> void
    {
       m_rotation_degrees += angles_degrees;
       compose();
    }

    auto transform::add_rotation(const float angle_z_degrees) -> void
    {
       m_rotation_degrees.z += angle_z_degrees;
       compose();
    }

    auto transform::set_scale(const glm::vec3& scale) -> void
    {
       m_scale = scale;
       compose();
    }

    auto transform::set_scale(const float uniform_scale) -> void
    {
       m_scale = glm::vec3(uniform_scale);
       compose();
    }

    auto transform::add_scale(const glm::vec3& scale) -> void
    {
       m_scale += scale;
       m_scale = glm::max(m_scale, glm::vec3(0.01f));
       compose();
    }

    auto transform::add_scale(const float uniform_scale) -> void
    {
       m_scale += glm::vec3(uniform_scale);
       m_scale = glm::max(m_scale, glm::vec3(0.01f));
       compose();
    }

    auto transform::set_model(const glm::mat4& model) -> void
    {
       m_model = model;
    }

    auto transform::get_scale() const -> glm::vec3
    {
       return m_scale;
    }

    auto transform::get_rotation() const -> glm::vec3
    {
       return m_rotation_degrees;
    }

    auto transform::get_translation() const -> glm::vec3
    {
       return m_translation;
    }

    auto transform::get_model() const -> glm::mat4
    {
       return m_model;
    }
}  // namespace sdlk