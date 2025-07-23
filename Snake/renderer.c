#include "renderer.h"

#include <stdlib.h>
#include <stdio.h>

#include "glfw_includes.h"
#include "shaders.h"

#define FAILURE 0
#define SUCCESS 1

#define COLOUR_BLACK      0.0f, 0.0f, 0.0f
#define COLOUR_GREY       0.5f, 0.5f, 0.5f
#define COLOUR_WHITE      1.0f, 1.0f, 1.0f
#define COLOUR_RED        255.0f, 0.0f, 0.0f
#define COLOUR_DARK_GREEN 0.0f, 100.0f, 0.0f
#define COLOUR_GREEN      0.0f, 138.0f, 0.0f

int init_renderer(game_state_t* game_state) {
	game_state->shader_program = create_shader("./Shaders/main.vert", "./Shaders/main.frag");
	if (game_state->shader_program == FAILURE) {
		fprintf(stderr, "Error: Failed to load shaders...");
		return FAILURE;
	}

	glUseProgram(game_state->shader_program);

	game_state->u_width_location    = glGetUniformLocation(game_state->shader_program, "u_width");
	game_state->u_height_location   = glGetUniformLocation(game_state->shader_program, "u_height");
	game_state->u_position_location = glGetUniformLocation(game_state->shader_program, "u_position");
	game_state->u_size_location     = glGetUniformLocation(game_state->shader_program, "u_size");
	game_state->u_colour_location   = glGetUniformLocation(game_state->shader_program, "u_colour");

	setup_geometry(&game_state->square_VAO, &game_state->square_VBO, &game_state->square_EBO);
	if (game_state->square_VAO == FAILURE ||
		game_state->square_VBO == FAILURE ||
		game_state->square_EBO == FAILURE) {
		glDeleteProgram(game_state->shader_program);
		return FAILURE;
	}

	glUniform1f(game_state->u_width_location, (GLfloat)game_state->GAME_WIDTH);
	glUniform1f(game_state->u_height_location, (GLfloat)game_state->GAME_HEIGHT);

	glUniform1f(game_state->u_size_location, game_state->SIZE);

	return SUCCESS;
}

void setup_geometry(uint32_t* VAO, uint32_t* VBO, uint32_t* EBO) {
	float SQUARE_VERTICES[] = {
		-1.0f, -1.0f,
		 1.0f, -1.0f,
		 1.0f,  1.0f,
		-1.0f,  1.0f
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

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), NULL);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}

void render(game_state_t* game_state) {
	glClearColor(COLOUR_BLACK, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// prepare to draw squares
	glUseProgram(game_state->shader_program);
	glBindVertexArray(game_state->square_VAO);

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
}

void cleanup(game_state_t* game_state) {
	glDeleteVertexArrays(1, &game_state->square_VAO);
	glDeleteBuffers(1, &game_state->square_VBO);
	glDeleteBuffers(1, &game_state->square_EBO);
	glDeleteProgram(game_state->shader_program);
}
