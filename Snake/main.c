#include <stdlib.h>
#include <stdio.h>

#include "window.h"
#include "input.h"

void error_callback(int error, const char* desc) {
	fprintf(stderr, "Error: %s\n", desc);
}

int main(void) {
	init_glfw(error_callback);

	GLFWmonitor* primary_monitor = glfwGetPrimaryMonitor();
	GLFWvidmode* video_mode = glfwGetVideoMode(primary_monitor);
	const int GAME_WIDTH  = (int)(video_mode->width * 0.75);
	const int GAME_HEIGHT = (int)(video_mode->height * 0.75);

	GLFWwindow* window = init_glfw_window(GAME_WIDTH, GAME_HEIGHT, "Snake",
		NULL, NULL);

	input_t* input = (input_t*)glfwGetWindowUserPointer(window);

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		glfwSwapBuffers(window);
	}

	glfwDestroyWindow(window);

	glfwTerminate();
	return EXIT_SUCCESS;
}
