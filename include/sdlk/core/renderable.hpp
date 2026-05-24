//
// Created by ricka on 2025-12-30.
//

#pragma once

#include <any>
#include <memory>
#include <optional>
#include <unordered_map>
#include <sdlk/core/geometry.hpp>
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
	    renderable_context m_context{};
		std::unique_ptr<geometry> m_geometry{};

	public:
		renderable() = default;

		explicit renderable(std::unique_ptr<geometry> geometry);

		virtual auto render(const std::shared_ptr<gl_program> &program) -> void;

	    auto get_context() -> renderable_context&;
	    auto set_context(const renderable_context &context) -> void;

	    template <typename T>
	    auto set_context(const std::string name, const T &value) -> void
	    {
	        this->m_context.set<T>(name, value);
	    }

	    template <typename T>
	    auto get_context(const std::string &name) -> std::optional<T>
	    {
	        return this->m_context.get<T>(name);
	    }

		virtual ~renderable() = default;
	};
}