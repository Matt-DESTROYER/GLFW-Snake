#include "file.h"

#include <stdlib.h>
#include <stdio.h>

char* read_file(const char* filename) {
	FILE* file = fopen(filename, "rb");
	if (!file) {
		fprintf(stderr, "Error: Failed to open file: %s\n", filename);
		return NULL;
	}

	if (fseek(file, 0, SEEK_END) != 0) {
		fprintf(stderr, "Error: Failed to seek to end of file: %s\n", filename);
		fclose(file);
		return NULL;
	}

	long file_size = ftell(file);
	if (file_size < 0) {
		fprintf(stderr, "Error: Failed to get file size: %s\n", filename);
		fclose(file);
		return NULL;
	}

	if (fseek(file, 0, SEEK_SET) != 0) {
		fprintf(stderr, "Error: Failed to seek to start of file: %s\n", filename);
		fclose(file);
		return NULL;
	}

	size_t length = (size_t)file_size;
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
