#include "Window.h"

#include <iostream>

namespace Loader {
	Window::Window(const glm::ivec2 size, const char *name, GLFWmonitor *monitor, GLFWwindow *share) :
			m_p_current_window_(glfwCreateWindow(size.x, size.y, name, monitor, share)),
			m_width_(size.x),
			m_height_(size.y) {
	}

	Window::~Window() {
		m_p_current_window_ = nullptr;
	}

	bool Window::init() const {
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        if (!m_p_current_window_) {
            std::cout << "glfwCreateWindow failed!" << std::endl;
            glfwTerminate();
            return false;
        }
        return true;
    }

    void Window::set_scroll_callback(GLFWscrollfun callback) const {
        glfwSetScrollCallback(m_p_current_window_, callback);
    }

    void Window::set_key_callback(const GLFWkeyfun callback) const {
        glfwSetKeyCallback(m_p_current_window_, callback);
    }

    void Window::set_window_size_callback(const GLFWwindowsizefun callback) const {
        glfwSetWindowSizeCallback(m_p_current_window_, callback);
    }

    void Window::set_mouse_callback(GLFWcursorposfun callback) const {
		glfwSetCursorPosCallback(m_p_current_window_, callback);
	}

	void Window::make_context_current() const {
		glfwMakeContextCurrent(m_p_current_window_);
	}
}