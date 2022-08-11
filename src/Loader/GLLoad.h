#ifndef SIENGINE_GLLOAD_H
#define SIENGINE_GLLOAD_H

namespace Loader {
	class GLLoad {
	public:
		static bool glfw_init();

		static bool glad_init();
	};
}

#endif //SIENGINE_GLLOAD_H