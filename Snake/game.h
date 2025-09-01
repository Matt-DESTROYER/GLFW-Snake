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

#define TICK_RATE   3.0
#define TICK_DELTA  (1.0 / TICK_RATE)

#define TITLE_WIDTH  1000
#define TITLE_HEIGHT 600

typedef enum game_scene {
	SCENE_MENU,
	SCENE_HOW,
	SCENE_CREDITS,
	SCENE_PLAYING,
	SCENE_GAME_OVER
} game_scene_t;

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
	game_scene_t scene;

	// TEMP
	GLint rect_shader_program;
	GLint rect_VAO;
	GLint rect_VBO;
	GLint rect_EBO;

	GLint u_screen_location;
	GLint u_position_location;
	GLint u_dimensions_location;
	GLint u_colour_location;

	GLint texture_shader_program;
	GLint u_texture_screen_dimensions_location;
	GLint u_texture_dimensions_location;
	GLint u_texture_position_location;

	GLuint texture_title;
} game_state_t;

void restart_game(game_state_t* game_state);
int init_game();
void game_loop(GLFWwindow* window, game_state_t* game_state);
void update(game_state_t* game_state, double delta_time, double current_time);
void end_game(GLFWwindow* window);

#endif
