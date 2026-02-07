#include "sprite.h"

#include <stdlib.h>
#include <stdio.h>

#include "shaders.h"

sprite_t* create_sprite(const char* image) {
	sprite_t* sprite = (sprite_t*)malloc(sizeof(sprite_t));
	if (sprite == NULL) {
		fprintf(stderr, "Error: Failed to allocate memory for sprite\n");
		return NULL;
	}
	sprite->position   = (point_t){ .x = 0, .y = 0 };
	sprite->dimensions = (point_t){ .x = 0, .y = 0 };
	sprite->scale      = (pointf_t){ .x = 1.0f, .y = 1.0f };
	sprite->shader_program = 0;
	sprite->texture        = 0;
	if (sprite_load_texture(sprite, image) != 0) {
		free(sprite);
		return NULL;
	}
	return sprite;
}
int sprite_load_texture(sprite_t* sprite, const char* image_path) {
	image_t* image = load_image(image_path);
	if (image == NULL) {
		return -1;
	}
	sprite->texture = create_texture(image);
	sprite->dimensions.x = image->width;
	sprite->dimensions.y = image->height;
	free_image(image);
	return 0;
}
void sprite_load_shader_program(sprite_t* sprite, GLint shader_program) {
	sprite->shader_program = shader_program;
}
void sprite_load_shader(sprite_t* sprite, const char* vertex_path, const char* fragment_path) {
	sprite->shader_program = create_shader_from_file(vertex_path, fragment_path);
}
void sprite_load_default_shader(sprite_t* sprite) {
	sprite_load_shader(sprite, DEFAULT_TEXTURE_VERTEX_SHADER, DEFAULT_TEXTURE_FRAGMENT_SHADER);
}
bool point_in_sprite(sprite_t* sprite, point_t point) {
	return point.x > sprite->position.x - sprite->dimensions.x * sprite->scale.x / 2.0f &&
		point.x < sprite->position.x + sprite->dimensions.x * sprite->scale.x / 2.0f &&
		point.y > sprite->position.y - sprite->dimensions.y * sprite->scale.y / 2.0f &&
		point.y < sprite->position.y + sprite->dimensions.y * sprite->scale.y / 2.0f;
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
