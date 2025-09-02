#ifndef SPRITE_H
#define SPRITE_H

#include "glfw_includes.h"
#include "images.h"
#include "point.h"

typedef struct sprite {
	char* name;
	point_t position;
	GLint shader_program;
	GLuint texture;
} sprite_t;

sprite_t* create_sprite(const char* name, point_t position);
image_t*  sprite_load_texture(sprite_t* sprite, const char* image_path);
void      sprite_load_shader(sprite_t* sprite, const char* vertex_path, const char* fragment_path);
void      sprite_load_shader_program(sprite_t* sprite, GLint shader_program);
void      free_sprite(sprite_t* sprite);

#endif
