#include "renderer.h"

#include <stdlib.h>
#include <stdio.h>

#include "glfw_includes.h"
#include "shaders.h"
#include "sprite.h"

#define FAILURE 0
#define SUCCESS 1

#define COLOUR_BLACK      0.0f, 0.0f, 0.0f
#define COLOUR_GREY       127.5f, 127.5f, 127.5f
#define COLOUR_WHITE      255.0f, 255.0f, 255.0f
#define COLOUR_RED        255.0f, 0.0f, 0.0f
#define COLOUR_DARK_GREEN 0.0f, 100.0f, 0.0f
#define COLOUR_GREEN      0.0f, 138.0f, 0.0f

int init_renderer(game_state_t* game_state) {
	game_state->rect_shader_program = create_shader_from_file("./Shaders/rect.vert", "./Shaders/rect.frag");
	if (game_state->rect_shader_program == FAILURE) {
		fprintf(stderr, "Error: Failed to load shaders...");
		return FAILURE;
	}

	game_state->texture_shader_program = create_shader_from_file("./Shaders/texture.vert", "./Shaders/texture.frag");
	if (game_state->texture_shader_program == FAILURE) {
		glDeleteProgram(game_state->rect_shader_program);
		fprintf(stderr, "Error: Failed to load texture shaders...");
		return FAILURE;
	}

	// enable transparency
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	game_state->u_screen_location     = glGetUniformLocation(game_state->rect_shader_program, "u_screen");
	game_state->u_position_location   = glGetUniformLocation(game_state->rect_shader_program, "u_position");
	game_state->u_dimensions_location = glGetUniformLocation(game_state->rect_shader_program, "u_dimensions");
	game_state->u_colour_location     = glGetUniformLocation(game_state->rect_shader_program, "u_colour");

	game_state->u_texture_screen_dimensions_location = glGetUniformLocation(game_state->texture_shader_program, "u_screen_dimensions");
	game_state->u_texture_dimensions_location        = glGetUniformLocation(game_state->texture_shader_program, "u_dimensions");
	game_state->u_texture_position_location          = glGetUniformLocation(game_state->texture_shader_program, "u_position");

	setup_geometry(&game_state->rect_VAO, &game_state->rect_VBO, &game_state->rect_EBO);
	if (game_state->rect_VAO == FAILURE ||
		game_state->rect_VBO == FAILURE ||
		game_state->rect_EBO == FAILURE) {
		glDeleteProgram(game_state->rect_shader_program);
		return FAILURE;
	}

	glUseProgram(game_state->rect_shader_program);
	glUniform2f(game_state->u_screen_location, (GLfloat)game_state->GAME_WIDTH, (GLfloat)game_state->GAME_HEIGHT);

	glUseProgram(game_state->texture_shader_program);
	glUniform2f(game_state->u_texture_screen_dimensions_location, (GLfloat)game_state->GAME_WIDTH, (GLfloat)game_state->GAME_HEIGHT);

	sprite_load_shader_program(game_state->back_arrow_sprite, game_state->texture_shader_program);

	sprite_load_shader_program(game_state->start_idle_sprite, game_state->texture_shader_program);
	sprite_load_shader_program(game_state->start_hover_sprite, game_state->texture_shader_program);
	sprite_load_shader_program(game_state->start_clicked_sprite, game_state->texture_shader_program);

	sprite_load_shader_program(game_state->credits_idle_sprite, game_state->texture_shader_program);
	sprite_load_shader_program(game_state->credits_hover_sprite, game_state->texture_shader_program);
	sprite_load_shader_program(game_state->credits_clicked_sprite, game_state->texture_shader_program);

	sprite_load_shader_program(game_state->title_sprite, game_state->texture_shader_program);
	sprite_load_shader_program(game_state->credits_chrissy_sprite, game_state->texture_shader_program);
	sprite_load_shader_program(game_state->credits_matty_sprite, game_state->texture_shader_program);
	sprite_load_shader_program(game_state->how_sprite, game_state->texture_shader_program);
	sprite_load_shader_program(game_state->game_over_sprite, game_state->texture_shader_program);
	sprite_load_shader_program(game_state->try_again_sprite, game_state->texture_shader_program);
	sprite_load_shader_program(game_state->score_sprite, game_state->texture_shader_program);

	sprite_load_shader_program(game_state->num_0_sprite, game_state->texture_shader_program);
	sprite_load_shader_program(game_state->num_1_sprite, game_state->texture_shader_program);
	sprite_load_shader_program(game_state->num_2_sprite, game_state->texture_shader_program);
	sprite_load_shader_program(game_state->num_3_sprite, game_state->texture_shader_program);
	sprite_load_shader_program(game_state->num_4_sprite, game_state->texture_shader_program);
	sprite_load_shader_program(game_state->num_5_sprite, game_state->texture_shader_program);
	sprite_load_shader_program(game_state->num_6_sprite, game_state->texture_shader_program);
	sprite_load_shader_program(game_state->num_7_sprite, game_state->texture_shader_program);
	sprite_load_shader_program(game_state->num_8_sprite, game_state->texture_shader_program);
	sprite_load_shader_program(game_state->num_9_sprite, game_state->texture_shader_program);

	return SUCCESS;
}

void setup_geometry(uint32_t* VAO, uint32_t* VBO, uint32_t* EBO) {
	float SQUARE_VERTICES[] = {
		-1.0f, -1.0f, 0.0f, 1.0f,
		 1.0f, -1.0f, 1.0f, 1.0f,
		 1.0f,  1.0f, 1.0f, 0.0f,
		-1.0f,  1.0f, 0.0f, 0.0f
	};
	uint32_t SQUARE_INDICES[] = {
		0, 1, 2,
		2, 3, 0
	};

	glGenVertexArrays(1, VAO);
	glGenBuffers(1, VBO);
	glGenBuffers(1, EBO);

	glBindVertexArray(*VAO);

	glBindBuffer(GL_ARRAY_BUFFER, *VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(SQUARE_VERTICES), SQUARE_VERTICES, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(SQUARE_INDICES), SQUARE_INDICES, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), NULL);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}

void render_menu(game_state_t* game_state) {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glBindVertexArray(game_state->rect_VAO);
	glUseProgram(game_state->texture_shader_program);
	glUniform2f(game_state->u_dimensions_location, game_state->SIZE, game_state->SIZE);

	// title/logo
	glUniform2f(game_state->u_texture_dimensions_location, (GLfloat)game_state->title_sprite->dimensions.x / 2.5f, (GLfloat)game_state->title_sprite->dimensions.y / 2.5f);
	glUniform2f(game_state->u_texture_position_location, 0, 225);
	glBindTexture(GL_TEXTURE_2D, game_state->title_sprite->texture);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	// start button
	sprite_t* start_button = game_state->start_idle_sprite;
	if (game_state->input.mouse.x > start_button->position.x - start_button->dimensions.x * start_button->scale.x / 2.0f &&
		game_state->input.mouse.x < start_button->position.x + start_button->dimensions.x * start_button->scale.x / 2.0f &&
		game_state->input.mouse.y > start_button->position.y - start_button->dimensions.y * start_button->scale.y / 2.0f &&
		game_state->input.mouse.y < start_button->position.y + start_button->dimensions.y * start_button->scale.y / 2.0f) {
		if (game_state->input.mouse_down) {
			start_button = game_state->start_clicked_sprite;
		} else {
			start_button = game_state->start_hover_sprite;
		}
	}
	glUniform2f(game_state->u_texture_dimensions_location, (GLfloat)start_button->dimensions.x * start_button->scale.x, (GLfloat)start_button->dimensions.y * start_button->scale.y);
	glUniform2f(game_state->u_texture_position_location, (GLfloat)start_button->position.x, (GLfloat)start_button->position.y);
	glBindTexture(GL_TEXTURE_2D, start_button->texture);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	// credits button
	sprite_t* credits_button = game_state->credits_idle_sprite;
	if (game_state->input.mouse.x > credits_button->position.x - credits_button->dimensions.x * credits_button->scale.x / 2.0f &&
		game_state->input.mouse.x < credits_button->position.x + credits_button->dimensions.x * credits_button->scale.x / 2.0f &&
		game_state->input.mouse.y > credits_button->position.y - credits_button->dimensions.y * credits_button->scale.y / 2.0f &&
		game_state->input.mouse.y < credits_button->position.y + credits_button->dimensions.y * credits_button->scale.y / 2.0f) {
		if (game_state->input.mouse_down) {
			credits_button = game_state->credits_clicked_sprite;
		}
		else {
			credits_button = game_state->credits_hover_sprite;
		}
	}
	glUniform2f(game_state->u_texture_dimensions_location, (GLfloat)credits_button->dimensions.x * credits_button->scale.x, (GLfloat)credits_button->dimensions.y * credits_button->scale.y);
	glUniform2f(game_state->u_texture_position_location, (GLfloat)credits_button->position.x, (GLfloat)credits_button->position.y);
	glBindTexture(GL_TEXTURE_2D, credits_button->texture);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

}
void render_game(game_state_t* game_state) {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// prepare to draw squares
	glBindVertexArray(game_state->rect_VAO);
	glUseProgram(game_state->rect_shader_program);
	glUniform2f(game_state->u_dimensions_location, game_state->SIZE, game_state->SIZE);

	// draw apple
	glUniform2f(game_state->u_position_location, game_state->apple.x * game_state->SIZE, game_state->apple.y * game_state->SIZE);
	glUniform4f(game_state->u_colour_location, COLOUR_RED, 1.0f);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	// draw snake head
	glUniform4f(game_state->u_colour_location, COLOUR_DARK_GREEN, 1.0f);
	glUniform2f(game_state->u_position_location, game_state->snake[0].x * game_state->SIZE, game_state->snake[0].y * game_state->SIZE);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	// draw snake body
	glUniform4f(game_state->u_colour_location, COLOUR_GREEN, 1.0f);
	for (size_t i = 1; i < game_state->food_count; i++) {
		glUniform2f(game_state->u_position_location, game_state->snake[i].x * game_state->SIZE, game_state->snake[i].y * game_state->SIZE);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

	// render border
	glUniform4f(game_state->u_colour_location, COLOUR_GREY, 1.0f);
	float width = (game_state->GAME_WIDTH - (float)GRID_WIDTH * game_state->SIZE) / 2;
	if (width > 0) {
		glUniform2f(game_state->u_dimensions_location, width, (GLfloat)game_state->GAME_HEIGHT);
		// left side
		glUniform2f(game_state->u_position_location, width / 2 - game_state->GAME_WIDTH / 2, 0);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		// right side
		glUniform2f(game_state->u_position_location, game_state->GAME_WIDTH / 2 - width / 2, 0);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
	float height = (game_state->GAME_HEIGHT - (float)GRID_HEIGHT * game_state->SIZE) / 2;
	if (height > 0) {
		glUniform2f(game_state->u_dimensions_location, (GLfloat)game_state->GAME_WIDTH, height);
		// left side
		glUniform2f(game_state->u_position_location, 0, height / 2 - game_state->GAME_HEIGHT / 2);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		// right side
		glUniform2f(game_state->u_position_location, 0, game_state->GAME_HEIGHT / 2 - height / 2);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
}
void render_game_over(game_state_t* game_state) {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void render(game_state_t* game_state) {
	switch (game_state->scene) {
		case SCENE_MENU:
			render_menu(game_state);
			break;
		case SCENE_PLAYING:
			render_game(game_state);
			break;
		case SCENE_GAME_OVER:
			render_game_over(game_state);
			break;
	}
}

void cleanup(game_state_t* game_state) {
	glDeleteVertexArrays(1, &game_state->rect_VAO);
	glDeleteBuffers(1, &game_state->rect_VBO);
	glDeleteBuffers(1, &game_state->rect_EBO);
	glDeleteProgram(game_state->rect_shader_program);
}
