#version 330 core

layout(location = 0) out vec4 colour;

in vec2 v_tex_coord;

uniform vec3 u_colour;

void main() {
	colour = vec4(u_colour,1.0);
}