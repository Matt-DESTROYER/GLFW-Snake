#include "sprite.h"

#include <stdlib.h>

sprite_t* create_sprite(const char* image) {
	sprite_t* sprite = (sprite_t*)malloc(sizeof(sprite_t));
	if (sprite == NULL) {
		return NULL;
	}
	sprite->position = (point_t){ .x=0, .y=0 };
	sprite->shader_program = 0;
	sprite->texture = 0;
	sprite_load_texture(sprite, image);
	sprite_load_shader(sprite, DEFAULT_TEXTURE_VERTEX_SHADER, DEFAULT_TEXTURE_FRAGMENT_SHADER);
	return sprite;
}
image_t* sprite_load_texture(sprite_t* sprite, const char* image_path) {
	image_t* image = load_image(image_path);
	sprite->texture = create_texture(image);
	return image;
}
void sprite_load_shader(sprite_t* sprite, const char* vertex_path, const char* fragment_path) {
	sprite->shader_program = create_shader_from_file(vertex_path, fragment_path);
}
void sprite_load_shader_program(sprite_t* sprite, GLint shader_program) {
	sprite->shader_program = shader_program;
}
void free_sprite(sprite_t* sprite) {
	if (sprite == NULL) {
		return;
	}
	if (sprite->texture != 0) {
		glDeleteTextures(1, &sprite->texture);
	}
	if (sprite->shader_program != 0) {
		glDeleteProgram(sprite->shader_program);
	}
	free(sprite);
}
