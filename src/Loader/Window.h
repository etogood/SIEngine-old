#pragma once

#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

namespace Loader
{
	class Window
	{
	public:
		Window() = delete;
		Window(const Window&) = delete;
		Window operator=(const Window&) = delete;

		Window(glm::ivec2 size, const char* name, GLFWmonitor* monitor, GLFWwindow* share);
		~Window();

		bool init() const;
		void set_key_call_back(GLFWkeyfun callback) const;
		void set_window_size_call_back(GLFWwindowsizefun callback) const;
		void make_context_current() const;

		GLFWwindow* get_window_pointer() const { return m_p_current_window_; };

		unsigned width() const { return m_width_; }
		unsigned height() const { return m_height_; }

	private:
		GLFWwindow* m_p_current_window_;
		unsigned m_width_ = 1080;
		unsigned m_height_ = 720;
	};
}
