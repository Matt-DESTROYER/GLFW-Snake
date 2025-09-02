#ifndef IMAGES_H
#define IMAGES_H

#include "glfw_includes.h"

typedef struct image {
	unsigned char* data;
	int width;
	int height;
	int channels;
} image_t;

image_t* load_image(const char* file);
void free_image(image_t* image);

GLuint create_texture(image_t* image);

#endif
