//
// Created by ricka on 2025-12-30.
//

#pragma once

#include <any>
#include <memory>
#include <optional>
#include <unordered_map>
#include <sdlk/core/geometry.hpp>
#include <sdlk/core/transform.hpp>
#include <sdlk/core/gl/gl_uniform.hpp>

namespace sdlk
{
        struct renderable_context
        {
            std::unordered_map<std::string, std::any> props{};

            template<typename T>
            auto get(const std::string& key) -> std::optional<T>
            {
                if (has(key))
                {
                    return std::any_cast<T>(props[key]);
                }

                return std::nullopt;
            }

            template<typename T>
            auto set(const std::string &key, T value)
            {
                this->props[key] = value;
            }

            auto has(const std::string &key) -> bool
            {
                return this->props.find(key) != this->props.end();
            }

            renderable_context() = default;
        };

	class renderable
	{
	protected:
		std::shared_ptr<geometry> m_geometry{};
		std::shared_ptr<transform> m_transform{std::make_shared<transform>()};
	    std::shared_ptr<renderable_context> m_context{std::make_shared<renderable_context>()};

	public:
		renderable() = default;

		explicit renderable(const std::shared_ptr<geometry> &geometry);

		virtual auto render(const std::shared_ptr<gl_program> &program) -> void;

	    auto get_context() -> std::shared_ptr<renderable_context>;
	    auto set_context(const std::shared_ptr<renderable_context> &context) -> void;

	    template <typename T>
	    auto set_context(const std::string name, const T &value) -> void
	    {
	        if (!this->m_context)
	        {
	            this->m_context = std::make_shared<renderable_context>();
	        }
	        this->m_context->set<T>(name, value);
	    }

	    template <typename T>
	    auto get_context(const std::string &name) -> std::optional<T>
	    {
	        if (!this->m_context)
	        {
	            return std::nullopt;
	        }

	        return this->m_context->get<T>(name);
	    }

		virtual ~renderable() = default;
	};
}