#version 330 core

layout (location = 0) in vec2 v_position;

uniform vec2 u_dimensions;
uniform vec2 u_position;
uniform float u_size;

void main() {
	vec2 position = (v_position * (u_size / 2)) / u_dimensions;
	position += u_position / u_dimensions;

	gl_Position = vec4(position, 0.0, 1.0);
}
