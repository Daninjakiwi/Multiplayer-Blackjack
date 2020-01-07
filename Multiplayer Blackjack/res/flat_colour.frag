#version 330 core

out vec4 colour;

uniform vec3 u_colour;

void main() {
	colour = vec4(u_colour,1.0);
}