#pragma once

#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

namespace Loader {
	class Window {
	public:
		Window() = delete;

		Window(const Window &) = delete;

		Window operator=(const Window &) = delete;

		Window(glm::ivec2 size, const char *name, GLFWmonitor *monitor, GLFWwindow *share);

		~Window();

		[[nodiscard]] bool init() const;

		void set_key_callback(GLFWkeyfun callback) const;

		void set_window_size_callback(GLFWwindowsizefun callback) const;

		void set_mouse_callback(GLFWcursorposfun callback) const;

		void make_context_current() const;

		[[nodiscard]] GLFWwindow *get_window_pointer() const { return m_p_current_window_; };

		[[nodiscard]] unsigned width() const { return m_width_; }

		[[nodiscard]] unsigned height() const { return m_height_; }

	private:
		GLFWwindow *m_p_current_window_;
		unsigned m_width_ = 1080;
		unsigned m_height_ = 720;
	};
}
