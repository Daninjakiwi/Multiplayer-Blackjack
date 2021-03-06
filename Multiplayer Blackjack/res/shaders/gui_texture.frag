#version 330 core

layout(location = 0) out vec4 colour;

in vec2 v_tex_coord;

uniform sampler2D u_texture;

void main() {
	vec4 col = texture(u_texture, v_tex_coord);
	
	if (col.a < 0.1) {
		discard;
	}

	colour = col;
}