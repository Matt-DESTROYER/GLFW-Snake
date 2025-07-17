#include "game.h"

#include <stdlib.h>
#include <stdio.h>

#include "glfw_includes.h"
#include "window.h"
#include "input.h"
#include "renderer.h"

void error_callback(int error, const char* desc) {
	fprintf(stderr, "Error: %s\n", desc);
}

int init_game(void) {
	if (init_glfw(error_callback) == -1) {
		return EXIT_FAILURE;
	}

	// calculate game window size (75% of screen size)
	GLFWmonitor* primary_monitor = glfwGetPrimaryMonitor();
	GLFWvidmode* video_mode = glfwGetVideoMode(primary_monitor);
	const int GAME_WIDTH = (int)(video_mode->width * 0.75);
	const int GAME_HEIGHT = (int)(video_mode->height * 0.75);

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	GLFWwindow* window = init_glfw_window(GAME_WIDTH, GAME_HEIGHT, "Snake",
		NULL, NULL);
	if (window == NULL) {
		return EXIT_FAILURE;
	}

	static game_state_t game_state;
	game_state.score = 0;
	game_state.high_score = 0;

	for (uint16_t i = 0; i < GRID_WIDTH * GRID_HEIGHT; i++) {
		game_state.snake[i].x = -1.0;
		game_state.snake[i].y = -1.0;
	}
	game_state.snake[0].x = (double)((int)(GRID_WIDTH * 0.25));
	game_state.snake[0].y = (double)((int)(GRID_HEIGHT * 0.5));

	game_state.food_count = 0;
	game_state.game_over  = false;
	game_state.paused     = false;
	game_state.speed      = 1.0;

	game_state.input.last_direction = INPUT_NULL;
	game_state.input.mouse.x = 0;
	game_state.input.mouse.y = 0;

	game_state.GAME_WIDTH  = GAME_WIDTH;
	game_state.GAME_HEIGHT = GAME_HEIGHT;
	
	glfwSetWindowUserPointer(window, &game_state.input);

	double previous_time = glfwGetTime();
	double current_time;
	double delta_time;

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		current_time = glfwGetTime();
		delta_time = current_time - previous_time;
		previous_time = current_time;

		update(&game_state, delta_time);
		render(&game_state);

		glfwSwapBuffers(window);
	}

	end_game(window);
	return EXIT_SUCCESS;
}

void update(game_state_t* game_state, double delta_time) {
}

void end_game(GLFWwindow* window) {
	glfwDestroyWindow(window);
	glfwTerminate();
}
