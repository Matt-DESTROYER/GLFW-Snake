#include "game.h"

#include <stdlib.h>
#include <stdio.h>

#include "glfw_includes.h"
#include "window.h"
#include "input.h"
#include "renderer.h"
#include "shaders.h"
#include "images.h"

void error_callback(int error, const char* desc) {
	fprintf(stderr, "Error: %s\n", desc);
}

void restart_game(game_state_t* game_state) {
	game_state->score = 0;

	game_state->snake[0].x = (float)((int)(GRID_WIDTH_LEFT / 2));
	game_state->snake[0].y = 0;

	game_state->apple.x = (float)((int)(GRID_WIDTH_RIGHT / 2));
	game_state->apple.y = 0;

	game_state->food_count = 1;
	game_state->game_over = false;
	game_state->paused = false;
	game_state->speed = 1.0;

	game_state->input.last_direction = INPUT_NULL;
}

int init_game() {
	if (init_glfw(error_callback) == FAILURE) {
		return EXIT_FAILURE;
	}

	// calculate game window size (75% of screen size)
	GLFWmonitor* primary_monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* video_mode = glfwGetVideoMode(primary_monitor);
	const int GAME_WIDTH = (int)(video_mode->width * 0.75);
	const int GAME_HEIGHT = (int)(video_mode->height * 0.75);

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	GLFWwindow* window = init_glfw_window(GAME_WIDTH, GAME_HEIGHT, "Snake",
		NULL, NULL);
	if (window == NULL) {
		return EXIT_FAILURE;
	}

	// initialise the game's state {
	static game_state_t game_state;
	game_state.high_score = 0;

	for (size_t i = 0; i < GRID_WIDTH * GRID_HEIGHT; i++) {
		game_state.snake[i].x = 0.0f;
		game_state.snake[i].y = 0.0f;
	}

	game_state.input.mouse.x = 0;
	game_state.input.mouse.y = 0;

	game_state.GAME_WIDTH  = (float)GAME_WIDTH;
	game_state.GAME_HEIGHT = (float)GAME_HEIGHT;
	game_state.SIZE = (float)GAME_WIDTH / (float)GRID_WIDTH;

	restart_game(&game_state);

	game_state.scene = SCENE_MENU;
	//game_state.scene = SCENE_PLAYING;
	// }

	// LOAD OUR FIRST IMAGE!!!
	image_t* image = load_image("Assets/title.png");
	game_state.texture_title = create_texture(image);
	free_image(image);
	
	glfwSetWindowUserPointer(window, &game_state);

	if (init_renderer(&game_state) == FAILURE) {
		end_game(window);
		return EXIT_FAILURE;
	}

	game_loop(window, &game_state);
	end_game(window);

	return EXIT_SUCCESS;
}

void game_loop(GLFWwindow* window, game_state_t* game_state) {
	double previous_time  = glfwGetTime();
	double current_time   = 0.0;
	double delta_time     = 0.0;
	game_state->last_tick = previous_time;

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		//printf("Scene: %i\n", game_state->scene);

		current_time = glfwGetTime();
		delta_time = current_time - previous_time;
		previous_time = current_time;

		update(game_state, delta_time, current_time);
		render(game_state);

		glfwSwapBuffers(window);
	}
}

void update_game(game_state_t * game_state, double delta_time, double current_time) {
	if (current_time - game_state->last_tick > TICK_DELTA) {
		// move snake {
		for (size_t i = 0; i < game_state->food_count - 1; i++) {
			size_t index = game_state->food_count - i - 1;
			
			game_state->snake[index].x = game_state->snake[index - 1].x;
			game_state->snake[index].y = game_state->snake[index - 1].y;
		}
		switch (game_state->input.new_direciton) {
			case INPUT_LEFT:
				game_state->snake[0].x--;
				break;
			case INPUT_UP:
				game_state->snake[0].y++;
				break;
			case INPUT_RIGHT:
				game_state->snake[0].x++;
				break;
			case INPUT_DOWN:
				game_state->snake[0].y--;
				break;
			default:
				break;
		}
		game_state->input.last_direction = game_state->input.new_direciton;
		game_state->last_tick = current_time;
		// }

		// boundary checks {
		if (game_state->snake[0].x < GRID_WIDTH_LEFT ||
			game_state->snake[0].x > GRID_WIDTH_RIGHT ||
			game_state->snake[0].y < GRID_HEIGHT_BOTTOM ||
			game_state->snake[0].y > GRID_HEIGHT_TOP) {
			game_state->game_over = true;
			printf("out of bounds detected...\n");
		}
		// }

		// self collision checks {
		for (size_t i = 1; i < game_state->food_count; i++) {
			if (game_state->snake[0].x == game_state->snake[i].x &&
				game_state->snake[0].y == game_state->snake[i].y) {
				game_state->game_over = true;
				printf("self collision detected...\n");
			}
		}
		// }

		//  apple collision checks {
		if (point_equal(&game_state->snake[0], &game_state->apple)) {
			game_state->snake[game_state->food_count].x = game_state->snake[game_state->food_count - 1].x;
			game_state->snake[game_state->food_count].y = game_state->snake[game_state->food_count - 1].y;
			game_state->food_count++;
			game_state->score++;

			// prevent apple from spawning inside snake
			bool in_snake = true;
			while (in_snake) {
				game_state->apple.x = (float)((rand() % GRID_WIDTH) + GRID_WIDTH_LEFT);
				game_state->apple.y = (float)((rand() % GRID_HEIGHT) + GRID_HEIGHT_BOTTOM);

				in_snake = false;
				for (size_t i = 0; i < game_state->food_count; i++) {
					if (point_equal(&game_state->snake[i], &game_state->apple)) {
						in_snake = true;
						break;
					}
				}
			}
		}
		// }
	}
}
void update(game_state_t* game_state, double delta_time, double current_time) {
	switch (game_state->scene) {
	case SCENE_MENU:
		break;
	case SCENE_PLAYING:
		update_game(game_state, delta_time, current_time);
		if (game_state->game_over) {
			if (game_state->score > game_state->high_score) {
				game_state->high_score = game_state->score;
			}
			game_state->scene = SCENE_GAME_OVER;
		}
		break;
	case SCENE_GAME_OVER:
		break;
	default:
		break;
	}
}

void end_game(GLFWwindow* window) {
	glfwDestroyWindow(window);
	glfwTerminate();
}
