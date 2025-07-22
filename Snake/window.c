#include <stdlib.h>

#include "window.h"
#include "input.h"

#define FAILURE 0
#define SUCCESS 1

int init_glfw(GLFWerrorfun error_callback) {
	glfwSetErrorCallback(error_callback);
	if (!glfwInit()) {
		return FAILURE;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwSetTime(0);

	return SUCCESS;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

GLFWwindow* init_glfw_window(int window_width, int window_height,
	const char* window_name, GLFWmonitor* monitor, GLFWwindow* share) {
	GLFWwindow* window = glfwCreateWindow(window_width, window_height,
		window_name, monitor, share);
	if (!window) {
		glfwTerminate();
		return NULL;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress)) {
		glfwTerminate();
		return NULL;
	}
	glfwSwapInterval(1);

	init_input(window);

	glViewport(0, 0, window_width, window_height);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	return window;
}
