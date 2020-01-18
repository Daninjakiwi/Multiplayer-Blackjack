#version 330 core

layout(location = 0) out vec4 colour;

in vec2 v_tex_coord;

uniform sampler2D u_texture;
uniform vec3 u_colour;

void main() {
	vec4 tex = texture(u_texture, v_tex_coord);
	if (tex.a < 0.1) {
		discard;
	}
	colour = vec4(u_colour,1.0);
}