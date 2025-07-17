#include "input.h"

#include "game.h"

static void key_callback(GLFWwindow* window, int key, int scancode,
	int action, int mods) {
	input_t* input = (input_t*)glfwGetWindowUserPointer(window);
	if (action == GLFW_PRESS) {
		switch (key) {
			case GLFW_KEY_A:
			case GLFW_KEY_LEFT:
				input->last_direction = INPUT_LEFT;
				break;

			case GLFW_KEY_W:
			case GLFW_KEY_UP:
				input->last_direction = INPUT_UP;
				break;

			case GLFW_KEY_D:
			case GLFW_KEY_RIGHT:
				input->last_direction = INPUT_RIGHT;
				break;

			case GLFW_KEY_S:
			case GLFW_KEY_DOWN:
				input->last_direction = INPUT_DOWN;
				break;
		}
	}
}

static void cursor_position_callback(GLFWwindow* window,
	double xpos, double ypos) {
	input_t* input = (input_t*)glfwGetWindowUserPointer(window);
	input->mouse.x = xpos;
	input->mouse.y = ypos;
}

void init_input(GLFWwindow* window) {
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
}
