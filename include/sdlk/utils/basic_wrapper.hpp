#include <string>

namespace sdlk
{
	void throw_if_not_success(int response, std::string message);
	namespace check
	{
		template<typename T>
		bool is_null(T *ptr)
		{
			return ptr == NULL || ptr == nullptr;
		}

		bool is_success(int response);
	}  // namespace check
}  // namespace sdlk
