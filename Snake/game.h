#ifndef SNAKE_GAME_STATE_H
#define SNAKE_GAME_STATE_H

#include <stdint.h>
#include <stdbool.h>

#include "glfw_includes.h"
#include "sprite.h"
#include "point.h"
#include "input.h"

#define GRID_WIDTH          19
#define GRID_HEIGHT         11
#define GRID_WIDTH_LEFT    -(GRID_WIDTH  / 2)
#define GRID_WIDTH_RIGHT    (GRID_WIDTH  / 2)
#define GRID_HEIGHT_TOP     (GRID_HEIGHT / 2)
#define GRID_HEIGHT_BOTTOM -(GRID_HEIGHT / 2)

#define TICK_RATE   3.0f
#define TICK_DELTA  (1.0f / TICK_RATE)

#define TITLE_WIDTH  500
#define TITLE_HEIGHT 300

typedef enum game_scene {
	SCENE_MENU,
	SCENE_HOW,
	SCENE_CREDITS,
	SCENE_PLAYING,
	SCENE_GAME_OVER
} game_scene_t;

typedef struct game_state {
	short score;
	short high_score;
	point_t snake[GRID_WIDTH * GRID_HEIGHT];
	point_t apple;
	short food_count;
	bool game_over;
	bool paused;
	double speed;
	input_t input;
	int GAME_WIDTH;
	int GAME_HEIGHT;
	float SIZE;
	double last_tick;
	game_scene_t scene;

	// TEMP
	GLuint rect_shader_program;
	GLint rect_VAO;
	GLint rect_VBO;
	GLint rect_EBO;

	GLint u_screen_location;
	GLint u_position_location;
	GLint u_dimensions_location;
	GLint u_colour_location;

	GLuint texture_shader_program;
	GLint u_texture_screen_dimensions_location;
	GLint u_texture_dimensions_location;
	GLint u_texture_position_location;

	GLuint texture_title;

	// sprites
	sprite_t* apple_sprite;

	sprite_t* back_arrow_sprite;

	sprite_t* start_idle_sprite;
	sprite_t* start_hover_sprite;
	sprite_t* start_clicked_sprite;

	sprite_t* credits_idle_sprite;
	sprite_t* credits_hover_sprite;
	sprite_t* credits_clicked_sprite;

	sprite_t* title_sprite;
	sprite_t* credits_chrissy_sprite;
	sprite_t* credits_matty_sprite;
	sprite_t* how_sprite;
	sprite_t* game_over_sprite;
	sprite_t* try_again_sprite;
	sprite_t* score_sprite;

	sprite_t* num_0_sprite;
	sprite_t* num_1_sprite;
	sprite_t* num_2_sprite;
	sprite_t* num_3_sprite;
	sprite_t* num_4_sprite;
	sprite_t* num_5_sprite;
	sprite_t* num_6_sprite;
	sprite_t* num_7_sprite;
	sprite_t* num_8_sprite;
	sprite_t* num_9_sprite;
} game_state_t;

void restart_game(game_state_t* game_state);
int init_game();
void game_loop(GLFWwindow* window, game_state_t* game_state);
void update(game_state_t* game_state, double delta_time, double current_time);
void on_click(game_state_t* game_state);
void end_game(GLFWwindow* window);

#endif
