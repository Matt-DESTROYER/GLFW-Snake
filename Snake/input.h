#ifndef SNAKE_INPUT_H
#define SNAKE_INPUT_H

#include "glfw_includes.h"
#include "point.h"


typedef enum direction {
	DIRECTION_NULL,
	DIRECTION_LEFT,
	DIRECTION_UP,
	DIRECTION_RIGHT,
	DIRECTION_DOWN
} direction_t;

typedef struct input {
	direction_t new_direction;
	direction_t last_direction;
	point_t mouse;
} input_t;

void init_input(GLFWwindow* window);

#endif
