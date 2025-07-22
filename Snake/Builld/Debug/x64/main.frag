#version 330 core
layout(location = 0) in vec4 u_colour;

out vec4 FragColor;

void main() {
	FragColor = u_colour;
}
