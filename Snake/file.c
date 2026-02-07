#include "file.h"

#include <stdlib.h>
#include <stdio.h>

char* read_file(const char* filename) {
	FILE* file = fopen(filename, "rb");
	if (!file) {
		return NULL;
	}

	if (fseek(file, 0, SEEK_END) != 0) {
		fclose(file);
		return NULL;
	}

	long file_size = ftell(file);
	if (file_size < 0) {
		fclose(file);
		return NULL;
	}

	if (fseek(file, 0, SEEK_SET) != 0) {
		fclose(file);
		return NULL;
	}

	size_t length = (size_t)file_size;
	char* buffer = (char*)malloc(sizeof(char) * (length + 1));
	if (!buffer) {
		fclose(file);
		return NULL;
	}

	if (fread(buffer, sizeof(char), length, file) < length) {
		fclose(file);
		free(buffer);
		return NULL;
	}
	buffer[length] = '\0';

	fclose(file);
	return buffer;
}
