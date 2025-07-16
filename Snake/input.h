#ifndef SNAKE_INPUT_H
#define SNAKE_INPUT_H

#include "glfw_includes.h"

#define INPUT_NULL  0
#define INPUT_LEFT  1
#define INPUT_UP    2
#define INPUT_RIGHT 3
#define INPUT_DOWN  4

typedef struct mouse {
	double x;
	double y;
} mouse_t;

typedef struct input {
	unsigned char last_direction;
	mouse_t mouse;
} input_t;

void init_input(GLFWwindow* window);

#endif
