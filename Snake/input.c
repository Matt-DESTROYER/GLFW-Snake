#include "input.h"

#include "glfw_includes.h"
#include "game.h"

void game_menu_input(game_state_t* game_state, int action, int key) {
	if (action == GLFW_PRESS) {
		switch (key) {
			case GLFW_KEY_ESCAPE:
				glfwSetWindowShouldClose(glfwGetCurrentContext(), true);
				break;
			case GLFW_KEY_SPACE:
			case GLFW_KEY_ENTER:
				game_state->scene = SCENE_PLAYING;
				break;
		}
	}
}
void game_playing_input(game_state_t* game_state, int action, int key) {
	if (action == GLFW_PRESS) {
		switch (key) {
			case GLFW_KEY_A:
			case GLFW_KEY_LEFT:
				if (game_state->input.last_direction != DIRECTION_RIGHT)
					game_state->input.new_direction = DIRECTION_LEFT;
				break;

			case GLFW_KEY_W:
			case GLFW_KEY_UP:
				if (game_state->input.last_direction != DIRECTION_DOWN)
					game_state->input.new_direction = DIRECTION_UP;
				break;

			case GLFW_KEY_D:
			case GLFW_KEY_RIGHT:
				if (game_state->input.last_direction != DIRECTION_LEFT)
					game_state->input.new_direction = DIRECTION_RIGHT;
				break;

			case GLFW_KEY_S:
			case GLFW_KEY_DOWN:
				if (game_state->input.last_direction != DIRECTION_UP)
					game_state->input.new_direction = DIRECTION_DOWN;
				break;

			case GLFW_KEY_P:
			case GLFW_KEY_ESCAPE:
				game_state->paused = !game_state->paused;
				break;
		}
	}
}
void game_over_input(game_state_t* game_state, int action, int key) {
	if (action == GLFW_PRESS) {
		switch (key) {
			case GLFW_KEY_ESCAPE:
				glfwSetWindowShouldClose(glfwGetCurrentContext(), true);
				break;
			case GLFW_KEY_SPACE:
			case GLFW_KEY_ENTER:
				restart_game(game_state);
				game_state->scene = SCENE_MENU;
				break;
		}
	}
}

static void key_callback(GLFWwindow* window, int key, int scancode,
	int action, int mods) {
	game_state_t* game_state = (game_state_t*)glfwGetWindowUserPointer(window);
	switch (game_state->scene) {
		case SCENE_MENU:
			game_menu_input(game_state, action, key);
			break;
		case SCENE_PLAYING:
			game_playing_input(game_state, action, key);
			break;
		case SCENE_GAME_OVER:
			game_over_input(game_state, action, key);
			break;
	}
}

static void cursor_position_callback(GLFWwindow* window,
	double xpos, double ypos) {
	game_state_t* game_state = (game_state_t*)glfwGetWindowUserPointer(window);
	game_state->input.mouse.x = (float)xpos;
	game_state->input.mouse.y = (float)ypos;
}

void init_input(GLFWwindow* window) {
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
}
