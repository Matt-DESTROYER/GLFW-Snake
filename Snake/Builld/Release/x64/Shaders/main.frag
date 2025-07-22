#version 330 core
layout(location = 0) in vec4 colour;

out vec4 FragColor;

void main() {
	FragColor = colour;
}
