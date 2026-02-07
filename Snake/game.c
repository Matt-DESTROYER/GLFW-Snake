#include "game.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "glfw_includes.h"
#include "window.h"
#include "input.h"
#include "renderer.h"
#include "shaders.h"
#include "images.h"

// Helper macro to check sprite creation
#define CHECK_SPRITE(sprite, path) \
	do { \
		sprite = create_sprite(path); \
		if (sprite == NULL) { \
			fprintf(stderr, "Error: Failed to create sprite from %s\n", path); \
			return EXIT_FAILURE; \
		} \
	} while(0)

void error_callback(int error, const char* desc) {
	fprintf(stderr, "Error: %s\n", desc);
}

void restart_game(game_state_t* game_state) {
	game_state->score = 0;

	game_state->snake[0].x = (int)(GRID_WIDTH_LEFT / 2);
	game_state->snake[0].y = 0;

	game_state->apple.x = (int)(GRID_WIDTH_RIGHT / 2);
	game_state->apple.y = 0;

	game_state->food_count = 1;
	game_state->game_over = false;
	game_state->paused = false;
	game_state->speed = 1.0;

	game_state->input.last_direction = DIRECTION_NULL;
	game_state->input.new_direction = DIRECTION_NULL;
}

float calc_size(int width, int height) {
	float cell_width = width / (float)GRID_WIDTH;
	float cell_height = height / (float)GRID_HEIGHT;
	if (cell_width < cell_height) {
		return cell_width;
	}
	return cell_height;
}

void window_size_callback(GLFWwindow* window, int width, int height) {
	game_state_t* game_state = (game_state_t*)glfwGetWindowUserPointer(window);

	game_state->GAME_WIDTH = width;
	game_state->GAME_HEIGHT = height;

	game_state->SIZE = calc_size(width, height);

	glUseProgram(game_state->rect_shader_program);
	glUniform2f(game_state->u_screen_location, (GLfloat)game_state->GAME_WIDTH, (GLfloat)game_state->GAME_HEIGHT);

	glUseProgram(game_state->texture_shader_program);
	glUniform2f(game_state->u_texture_screen_dimensions_location, (GLfloat)game_state->GAME_WIDTH, (GLfloat)game_state->GAME_HEIGHT);

	// (so we can see the resizing in real-time)
	render(game_state);
	glfwSwapBuffers(window);
	glFinish(); // make sure all rendering is finished before allowing anything to continue
}

int init_game() {
	// Seed random number generator
	srand((unsigned int)time(NULL));

	if (init_glfw(error_callback) == FAILURE) {
		return EXIT_FAILURE;
	}

	// calculate game window size (75% of screen size)
	GLFWmonitor* primary_monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* video_mode = glfwGetVideoMode(primary_monitor);
	const int GAME_WIDTH = (int)(video_mode->width * 0.75);
	const int GAME_HEIGHT = (int)(video_mode->height * 0.75);

	//glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	GLFWwindow* window = init_glfw_window(GAME_WIDTH, GAME_HEIGHT, "Snake",
		NULL, NULL);
	if (window == NULL) {
		return EXIT_FAILURE;
	}

	glfwSetWindowSizeCallback(window, (GLFWwindowsizefun)window_size_callback);

	// initialise the game's state {
	static game_state_t game_state;
	game_state.high_score = 0;

	for (size_t i = 0; i < GRID_WIDTH * GRID_HEIGHT; i++) {
		game_state.snake[i].x = 0;
		game_state.snake[i].y = 0;
	}

	game_state.input.mouse.x = 0;
	game_state.input.mouse.y = 0;

	game_state.GAME_WIDTH  = GAME_WIDTH;
	game_state.GAME_HEIGHT = GAME_HEIGHT;

	game_state.SIZE = calc_size(GAME_WIDTH, GAME_HEIGHT);

	restart_game(&game_state);

	game_state.scene = SCENE_MENU;
	// }

	// load sprites {
	CHECK_SPRITE(game_state.back_arrow_sprite, "./Assets/back-arrow.png");
	game_state.back_arrow_sprite->scale = (pointf_t){ .x = 0.2f, .y = 0.2f };
	game_state.back_arrow_sprite->position = (point_t){
		.x = (int)((float)game_state.back_arrow_sprite->dimensions.x * game_state.back_arrow_sprite->scale.x - (float)game_state.GAME_WIDTH / 2.0f),
		.y = (int)((float)game_state.GAME_HEIGHT / 2.0f - (float)game_state.back_arrow_sprite->dimensions.y * game_state.back_arrow_sprite->scale.y)
	};

	pointf_t button_scale   = (pointf_t){ .x = 0.2f, .y = 0.2f };

	point_t start_sprite_position = (point_t){ .x = 0, .y = 25 };
	CHECK_SPRITE(game_state.start_idle_sprite, "./Assets/start-button-idle.png");
	game_state.start_idle_sprite->position = start_sprite_position;
	game_state.start_idle_sprite->scale    = button_scale;
	CHECK_SPRITE(game_state.start_hover_sprite, "./Assets/start-button-hover.png");
	game_state.start_hover_sprite->position = start_sprite_position;
	game_state.start_hover_sprite->scale = button_scale;
	CHECK_SPRITE(game_state.start_clicked_sprite, "./Assets/start-button-clicked.png");
	game_state.start_clicked_sprite->position = start_sprite_position;
	game_state.start_clicked_sprite->scale = button_scale;

	point_t cancel_sprite_position = (point_t){ .x = 0, .y = -100 };
	CHECK_SPRITE(game_state.credits_idle_sprite, "./Assets/credits-button-idle.png");
	game_state.credits_idle_sprite->position = cancel_sprite_position;
	game_state.credits_idle_sprite->scale = button_scale;
	CHECK_SPRITE(game_state.credits_hover_sprite, "./Assets/credits-button-hover.png");
	game_state.credits_hover_sprite->position = cancel_sprite_position;
	game_state.credits_hover_sprite->scale = button_scale;
	CHECK_SPRITE(game_state.credits_clicked_sprite, "./Assets/credits-button-clicked.png");
	game_state.credits_clicked_sprite->position = cancel_sprite_position;
	game_state.credits_clicked_sprite->scale = button_scale;

	CHECK_SPRITE(game_state.title_sprite, "./Assets/logo-green.png");
	game_state.title_sprite->position = (point_t){ .x = 0, .y = 225 };
	game_state.title_sprite->scale = (pointf_t){ .x = 0.2f, .y = 0.2f };
	CHECK_SPRITE(game_state.credits_matty_sprite, "./Assets/credits-matty.png");
	game_state.credits_matty_sprite->position = (point_t){ .x = 0, .y = 0 };
	game_state.credits_matty_sprite->scale = (pointf_t){ .x = 0.5f, .y = 0.5f };
	CHECK_SPRITE(game_state.credits_chrissy_sprite, "./Assets/credits-chrissy.png");
	game_state.credits_chrissy_sprite->position = (point_t){ .x = 0, .y = -75 };
	game_state.credits_chrissy_sprite->scale = (pointf_t){ .x = 0.5f, .y = 0.5f };
	CHECK_SPRITE(game_state.how_sprite, "./Assets/how-button.png");
	CHECK_SPRITE(game_state.game_over_sprite, "./Assets/game-over.png");
	game_state.game_over_sprite->position = (point_t){ .x = 0, .y = 200 };
	game_state.game_over_sprite->scale = (pointf_t){ .x = 0.75f, .y = 0.75f };
	CHECK_SPRITE(game_state.try_again_sprite, "./Assets/try-again.png");
	game_state.try_again_sprite->position = (point_t){ .x = 0, .y = -200 };
	game_state.try_again_sprite->scale = (pointf_t){ .x = 0.5f, .y = 0.5f };
	CHECK_SPRITE(game_state.score_sprite, "./Assets/score.png");
	game_state.score_sprite->scale = (pointf_t){ .x = 0.1f, .y = 0.1f };

	pointf_t number_scale = (pointf_t){ .x = 0.125f, .y = 0.125f };
	CHECK_SPRITE(game_state.num_0_sprite, "./Assets/0.png");
	game_state.num_0_sprite->scale = number_scale;
	CHECK_SPRITE(game_state.num_1_sprite, "./Assets/1.png");
	game_state.num_1_sprite->scale = number_scale;
	CHECK_SPRITE(game_state.num_2_sprite, "./Assets/2.png");
	game_state.num_2_sprite->scale = number_scale;
	CHECK_SPRITE(game_state.num_3_sprite, "./Assets/3.png");
	game_state.num_3_sprite->scale = number_scale;
	CHECK_SPRITE(game_state.num_4_sprite, "./Assets/4.png");
	game_state.num_4_sprite->scale = number_scale;
	CHECK_SPRITE(game_state.num_5_sprite, "./Assets/5.png");
	game_state.num_5_sprite->scale = number_scale;
	CHECK_SPRITE(game_state.num_6_sprite, "./Assets/6.png");
	game_state.num_6_sprite->scale = number_scale;
	CHECK_SPRITE(game_state.num_7_sprite, "./Assets/7.png");
	game_state.num_7_sprite->scale = number_scale;
	CHECK_SPRITE(game_state.num_8_sprite, "./Assets/8.png");
	game_state.num_8_sprite->scale = number_scale;
	CHECK_SPRITE(game_state.num_9_sprite, "./Assets/9.png");
	game_state.num_9_sprite->scale = number_scale;
	// }
	
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
		switch (game_state->input.new_direction) {
			case DIRECTION_LEFT:
				game_state->snake[0].x--;
				break;
			case DIRECTION_UP:
				game_state->snake[0].y++;
				break;
			case DIRECTION_RIGHT:
				game_state->snake[0].x++;
				break;
			case DIRECTION_DOWN:
				game_state->snake[0].y--;
				break;
			default:
				break;
		}
		game_state->input.last_direction = game_state->input.new_direction;
		game_state->last_tick = current_time;
		// }

		// boundary checks {
		if (game_state->snake[0].x < GRID_WIDTH_LEFT ||
			game_state->snake[0].x > GRID_WIDTH_RIGHT ||
			game_state->snake[0].y < GRID_HEIGHT_BOTTOM ||
			game_state->snake[0].y > GRID_HEIGHT_TOP) {
			game_state->game_over = true;
		}
		// }

		// self collision checks {
		for (size_t i = 1; i < game_state->food_count; i++) {
			if (game_state->snake[0].x == game_state->snake[i].x &&
				game_state->snake[0].y == game_state->snake[i].y) {
				game_state->game_over = true;
			}
		}
		// }

		//  apple collision checks {
		if (game_state->snake[0].x == game_state->apple.x &&
			game_state->snake[0].y == game_state->apple.y) {
			game_state->snake[game_state->food_count].x = game_state->snake[game_state->food_count - 1].x;
			game_state->snake[game_state->food_count].y = game_state->snake[game_state->food_count - 1].y;
			game_state->food_count++;
			game_state->score++;

			// prevent apple from spawning inside snake
			bool in_snake = true;
			while (in_snake) {
				game_state->apple.x = (rand() % GRID_WIDTH) + GRID_WIDTH_LEFT;
				game_state->apple.y = (rand() % GRID_HEIGHT) + GRID_HEIGHT_BOTTOM;

				in_snake = false;
				for (size_t i = 0; i < game_state->food_count; i++) {
					if (game_state->snake[i].x == game_state->apple.x &&
						game_state->snake[i].y == game_state->apple.y) {
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
		case SCENE_HOW:
		case SCENE_CREDITS:
		case SCENE_GAME_OVER:
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
		default:
			break;
	}
}

void on_click(game_state_t* game_state) {
	switch (game_state->scene) {
		case SCENE_PLAYING:
			break;
		case SCENE_MENU:
			if (point_in_sprite(game_state->start_clicked_sprite, game_state->input.mouse)) {
				game_state->scene = SCENE_PLAYING;
			} else if (point_in_sprite(game_state->credits_clicked_sprite, game_state->input.mouse)) {
				game_state->scene = SCENE_CREDITS;
			}
			break;
		case SCENE_HOW:
			break;
		case SCENE_CREDITS:
			if (point_in_sprite(game_state->back_arrow_sprite, game_state->input.mouse)) {
				game_state->scene = SCENE_MENU;
			}
			break;
		case SCENE_GAME_OVER:
			if (point_in_sprite(game_state->back_arrow_sprite, game_state->input.mouse)) {
				game_state->scene = SCENE_MENU;
			}
			break;
		default:
			break;
	}
}

void cleanup_sprites(game_state_t* game_state) {
	// Free all sprites
	free_sprite(game_state->back_arrow_sprite);
	free_sprite(game_state->start_idle_sprite);
	free_sprite(game_state->start_hover_sprite);
	free_sprite(game_state->start_clicked_sprite);
	free_sprite(game_state->credits_idle_sprite);
	free_sprite(game_state->credits_hover_sprite);
	free_sprite(game_state->credits_clicked_sprite);
	free_sprite(game_state->title_sprite);
	free_sprite(game_state->credits_chrissy_sprite);
	free_sprite(game_state->credits_matty_sprite);
	free_sprite(game_state->how_sprite);
	free_sprite(game_state->game_over_sprite);
	free_sprite(game_state->try_again_sprite);
	free_sprite(game_state->score_sprite);
	free_sprite(game_state->num_0_sprite);
	free_sprite(game_state->num_1_sprite);
	free_sprite(game_state->num_2_sprite);
	free_sprite(game_state->num_3_sprite);
	free_sprite(game_state->num_4_sprite);
	free_sprite(game_state->num_5_sprite);
	free_sprite(game_state->num_6_sprite);
	free_sprite(game_state->num_7_sprite);
	free_sprite(game_state->num_8_sprite);
	free_sprite(game_state->num_9_sprite);
}

void end_game(GLFWwindow* window) {
	game_state_t* game_state = (game_state_t*)glfwGetWindowUserPointer(window);
	if (game_state != NULL) {
		cleanup_sprites(game_state);
		cleanup(game_state);
	}
	glfwDestroyWindow(window);
	glfwTerminate();
}
