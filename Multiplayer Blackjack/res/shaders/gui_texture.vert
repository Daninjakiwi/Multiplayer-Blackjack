#version 330 core

layout (location=0) in vec2 position;
layout (location=1) in vec2 tex_coord;

out vec2 v_tex_coord;

uniform mat4 u_camera;

void main() {
	gl_Position = u_camera * vec4(position,0.0,1.0);
	v_tex_coord = tex_coord;
}