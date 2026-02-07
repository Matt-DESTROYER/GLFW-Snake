#ifndef SPRITE_H
#define SPRITE_H

#include "glfw_includes.h"
#include "images.h"
#include "point.h"

#define DEFAULT_TEXTURE_VERTEX_SHADER   "./Assets/texture.vert"
#define DEFAULT_TEXTURE_FRAGMENT_SHADER "./Assets/texture.frag"

typedef struct sprite {
	point_t position;
	point_t dimensions;
	pointf_t scale;
	GLint shader_program;
	GLuint texture;
} sprite_t;

sprite_t* create_sprite(const char* name);
int       sprite_load_texture(sprite_t* sprite, const char* image_path);
void      sprite_load_shader_program(sprite_t* sprite, GLint shader_program);
void      sprite_load_shader(sprite_t* sprite, const char* vertex_path, const char* fragment_path);
void      sprite_load_default_shader(sprite_t* sprite);
bool      point_in_sprite(sprite_t* sprite, point_t point);
void      free_sprite(sprite_t* sprite);

#endif
