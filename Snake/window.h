#ifndef WINDOW_H
#define WINDOW_H

#include "glfw_includes.h"

void init_glfw(GLFWerrorfun error_callback);

GLFWwindow* init_glfw_window(int window_width, int window_height,
	const char* window_name, GLFWmonitor* monitor, GLFWwindow* share);

#endif
