#include <stdlib.h>

#include "window.h"
#include "input.h"

int init_glfw(GLFWerrorfun error_callback) {
	glfwSetErrorCallback(error_callback);
	if (!glfwInit()) {
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwSetTime(0);

	return 0;
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

	gladLoadGL(glfwGetProcAddress);
	glfwSwapInterval(1);

	init_input(window);

	return window;
}
