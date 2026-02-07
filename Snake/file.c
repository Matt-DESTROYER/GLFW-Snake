#include "file.h"

#include <stdlib.h>
#include <stdio.h>

char* read_file(const char* filename) {
	FILE* file = fopen(filename, "rb");
	if (!file) {
		fprintf(stderr, "Error: Failed to open file: %s\n", filename);
		return NULL;
	}

	fseek(file, 0, SEEK_END);
	size_t length = ftell(file);
	fseek(file, 0, SEEK_SET);

	char* buffer = (char*)malloc(sizeof(char) * (length + 1));
	if (!buffer) {
		fprintf(stderr, "Error: Failed to allocate memory for file: %s\n", filename);
		fclose(file);
		return NULL;
	}

	if (fread(buffer, sizeof(char), length, file) < length) {
		fprintf(stderr, "Error: Failed to read complete file: %s\n", filename);
		fclose(file);
		free(buffer);
		return NULL;
	}
	buffer[length] = '\0';

	fclose(file);
	return buffer;
}
