#ifndef SNAKE_SHADERS_H
#define SNAKE_SHADERS_H

#include "glfw_includes.h"

#define FAILURE 0
#define SUCCESS 1

GLint create_shader(const char* vertex_shader, const char* fragment_shader);

#endif
