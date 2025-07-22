#version 330 core

layout (location = 0) in vec2 aPos;

uniform float u_width;
uniform float u_height;
uniform vec2 u_position;
uniform float u_size;
uniform vec4 u_colour;

layout(location = 0) out vec4 v_colour;

void main() {
	vec2 position = aPos * vec2(u_size / u_width, u_size / u_height) + u_position;
	position.x = (position.x / u_width) * 2.0 - 1.0;
	position.y = -((position.y / u_height) * 2.0 - 1.0);
	gl_Position = vec4(position, 0.0, 1.0);
	v_colour = u_colour / 255.0f;
}
