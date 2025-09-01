#version 330 core

layout (location = 0) in vec2 v_position;

uniform vec2 u_screen;
uniform vec2 u_position;
uniform vec2 u_dimensions;

void main() {
	vec2 position = (v_position * (u_dimensions / 2)) / u_screen;
	position += u_position / u_screen;

	gl_Position = vec4(position, 0.0, 1.0);
}
