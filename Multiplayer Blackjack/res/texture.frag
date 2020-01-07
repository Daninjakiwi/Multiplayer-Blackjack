#version 330 core

out vec4 colour;

in vec2 v_tex_coord;

uniform sampler2D u_texture;

void main() {

	vec4 tex_colour = texture(u_texture, v_tex_coord);
	colour = tex_colour;
}