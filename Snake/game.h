#ifndef SNAKE_GAME_STATE_H
#define SNAKE_GAME_STATE_H

#include "glfw_includes.h"
#include "point.h"

#include <stdint.h>
#include <stdbool.h>

#define GRID_WIDTH 16
#define GRID_HEIGHT 9

typedef struct input {
	unsigned char last_direction;
	point_t mouse;
} input_t;

typedef struct game_state {
	uint16_t score;
	uint16_t high_score;
	point_t snake[GRID_WIDTH * GRID_HEIGHT];
	uint16_t food_count;
	bool game_over;
	bool paused;
	double speed;
	input_t input;
	int GAME_WIDTH;
	int GAME_HEIGHT;
} game_state_t;

int init_game(void);
void update(game_state_t* game_state, double delta_time);
void end_game(GLFWwindow* window);

#endif
