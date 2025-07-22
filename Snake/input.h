#ifndef SNAKE_INPUT_H
#define SNAKE_INPUT_H

#include "glfw_includes.h"
#include "point.h"

#define INPUT_NULL  0
#define INPUT_LEFT  1
#define INPUT_UP    2
#define INPUT_RIGHT 3
#define INPUT_DOWN  4

typedef struct input {
	unsigned char new_direciton;
	unsigned char last_direction;
	point_t mouse;
} input_t;

void init_input(GLFWwindow* window);

#endif
