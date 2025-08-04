#version 330 core

uniform vec4 u_colour;

out vec4 FragColor;

void main() {
	FragColor = u_colour / 255.0f;
}
