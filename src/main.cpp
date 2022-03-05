#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

// ReSharper disable once IdentifierTypo
void glfw_window_size_callback(GLFWwindow* p_window, int width, int height)
{
	
}

void main(){

	if (!glfwInit())
	{
		std::cerr << "Can't initialize glfw";
		return;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

}