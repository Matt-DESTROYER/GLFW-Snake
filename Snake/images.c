#include "images.h"

#include <stdlib.h>
#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#define RGB_CHANNELS  3
#define RGBA_CHANNELS 4

image_t* load_image(const char* file) {
	image_t* image = malloc(sizeof(image_t));
	if (image == NULL) {
		fprintf(stderr, "Error: Failed to allocate memory for image\n");
		return NULL;
	}

	image->data = stbi_load(file, &image->width, &image->height, &image->channels, RGBA_CHANNELS);
	
	if (image->data == NULL) {
		fprintf(stderr, "Error: Failed to load image: %s\n", file);
		fprintf(stderr, "STB Error: %s\n", stbi_failure_reason());
		free(image);
		return NULL;
	}

	return image;
}

void free_image(image_t* image) {
	if (image == NULL) {
		return;
	}
	if (image->data != NULL) {
		stbi_image_free(image->data);
	}
	free(image);
}

GLuint create_texture(image_t* image) {
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->width, image->height,
					 0, GL_RGBA, GL_UNSIGNED_BYTE, image->data);
	glGenerateMipmap(GL_TEXTURE_2D);

	return texture;
}
