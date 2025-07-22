#ifndef SNAKE_RENDERER_H
#define SNAKE_RENDERER_H

#include "glfw_includes.h"
#include "game.h"

int init_renderer(game_state_t* game_state);
void setup_geometry(uint32_t* VAO, uint32_t* VBO, uint32_t* EBO);
void render(game_state_t* game_state);

#endif
