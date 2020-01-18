#version 330 core

layout(location = 0) out vec4 colour;

in vec2 v_tex_coord;

uniform vec4 u_colour;

void main() {
	vec3 col = vec3(u_colour.r, u_colour.g, u_colour.b);
	colour = u_colour;
}