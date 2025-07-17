#ifndef SNAKE_INPUT_H
#define SNAKE_INPUT_H

#include "glfw_includes.h"

#define INPUT_NULL  0
#define INPUT_LEFT  1
#define INPUT_UP    2
#define INPUT_RIGHT 3
#define INPUT_DOWN  4

void init_input(GLFWwindow* window);

#endif
