#ifndef SNAKE_SHADERS_H
#define SNAKE_SHADERS_H

#include "glfw_includes.h"

#define FAILURE 0
#define SUCCESS 1

GLuint create_shader(char* vertex_shader_source, char* fragment_shader_source);
GLuint create_shader_from_file(const char* vertex_shader_file, const char* fragment_shader_file);

#endif
