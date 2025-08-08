#ifndef SPRITE_H
#define SPRITE_H

#include "glfw_includes.h"
#include "images.h"

typedef struct uniform_list_node {
	char* name;
	GLint location;

	uniform_list_node_t* next;
} uniform_list_node_t;

typedef struct uniform_list {
	size_t length;
	uniform_list_node* head;
	uniform_list_node* tail;
} uniform_list_t;

typedef struct sprite {
	char* name;

	uniform_list_t uniforms;

	GLint shader_program;
} sprite_t;

#endif
