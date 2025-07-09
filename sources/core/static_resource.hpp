#include <glad/glad.h>

#include <string>

namespace sdlk
{
	class resource
	{
	private:
		static std::string s_vertex_source, s_fragment_source;

	public:
		friend class app;
	};
}  // namespace sdlk
