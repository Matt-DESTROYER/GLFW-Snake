#version 330 core

uniform vec4 u_colour;

out vec4 FragColor;

void main() {
	// normalise colour from 0-255 to 0-1
	FragColor = vec4(u_colour.rgb / 255.0f, u_colour.a);
}
