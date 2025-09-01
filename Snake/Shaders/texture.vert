#version 330 core

layout (location = 0) in vec2 v_position;
layout (location = 1) in vec2 v_TexCoord;

uniform vec2 u_screen_dimensions;
uniform vec2 u_dimensions;
uniform vec2 u_position;

out vec2 TexCoord;

void main() {
	vec2 position = (v_position * (u_dimensions / 2)) / u_screen_dimensions; // scaling
	position += u_position / u_screen_dimensions; // translation

	gl_Position = vec4(2 * position, 0.0, 1.0);

	TexCoord = v_TexCoord;
}
