#version 330 core

layout (location = 0) in vec2 v_position;

uniform float u_width;
uniform float u_height;
uniform vec2 u_position;
uniform float u_size;

void main() {
	vec2 position = v_position * (u_size / 2);
	position.x /= u_width;
	position.y /= u_height;

	
	vec2 translation = vec2(
		u_position.x / u_width,
		u_position.y / u_height
	);
	position += translation;

	gl_Position = vec4(position, 0.0, 1.0);
}
