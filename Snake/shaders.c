#include "shaders.h"

#include <stdlib.h>
#include <stdio.h>

#include "file.h"

GLuint create_shader(char* vertex_shader_source, char* fragment_shader_source) {
	GLint success;

	GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, (const char**)&vertex_shader_source, NULL);
	glCompileShader(vertex_shader);

	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog);
		fprintf(stderr, "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s\n", infoLog);
		glDeleteShader(vertex_shader);
		return FAILURE;
	}

	GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, (const char**)&fragment_shader_source, NULL);
	glCompileShader(fragment_shader);
	
	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetShaderInfoLog(fragment_shader, 512, NULL, infoLog);
		fprintf(stderr, "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s\n", infoLog);
		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);
		return FAILURE;
	}

	GLuint shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	glLinkProgram(shader_program);

	glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetProgramInfoLog(shader_program, 512, NULL, infoLog);
		glDeleteProgram(shader_program);
		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);
		return FAILURE;
	}

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	return shader_program;
}

GLuint create_shader_from_file(const char* vertex_shader_file, const char* fragment_shader_file) {
	char* vertex_shader_source = read_file(vertex_shader_file);
	if (vertex_shader_source == NULL) {
		return FAILURE;
	}

	char* fragment_shader_source = read_file(fragment_shader_file);
	if (fragment_shader_source == NULL) {
		free(vertex_shader_source);
		return FAILURE;
	}

	GLuint shader_program = create_shader(vertex_shader_source, fragment_shader_source);

	free(vertex_shader_source);
	free(fragment_shader_source);

	return shader_program;
}
