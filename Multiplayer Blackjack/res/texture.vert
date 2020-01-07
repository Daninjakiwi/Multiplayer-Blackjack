#version 330 core

layout (location=0) in vec3 position;
layout(location = 1) in vec2 tex_coord;

out vec2 v_tex_coord;

uniform mat4 u_camera;
uniform mat4 u_transform;

void main() {
	gl_Position = u_camera * u_transform * vec4(position,1.0);
	
	v_tex_coord = tex_coord;
}