#ifndef SNAKE_GAME_STATE_H
#define SNAKE_GAME_STATE_H

#include <stdint.h>
#include <stdbool.h>

#include "glfw_includes.h"
#include "point.h"
#include "input.h"

#define GRID_WIDTH          16
#define GRID_HEIGHT         9
#define GRID_WIDTH_LEFT    -(GRID_WIDTH / 2)
#define GRID_WIDTH_RIGHT    (GRID_WIDTH / 2)
#define GRID_HEIGHT_TOP     (GRID_HEIGHT / 2)
#define GRID_HEIGHT_BOTTOM -(GRID_HEIGHT / 2)

#define TICK_RATE   2.0
#define TICK_DELTA  (1.0 / TICK_RATE)

typedef struct game_state {
	uint32_t score;
	uint32_t high_score;
	point_t snake[GRID_WIDTH * GRID_HEIGHT];
	point_t apple;
	uint32_t food_count;
	bool game_over;
	bool paused;
	double speed;
	input_t input;
	float GAME_WIDTH;
	float GAME_HEIGHT;
	float SIZE;
	double last_tick;

	// TEMP
	GLint shader_program;
	GLint square_VAO;
	GLint square_VBO;
	GLint square_EBO;
	GLint u_width_location;
	GLint u_height_location;
	GLint u_position_location;
	GLint u_size_location;
	GLint u_colour_location;
} game_state_t;

int init_game(void);
void game_loop(GLFWwindow* window, game_state_t* game_state);
void update(game_state_t* game_state, double delta_time, double current_time);
void end_game(GLFWwindow* window);

#endif
