#version 330 core

layout (location=0) in vec3 position;
layout (location=1) in vec3 normal;
layout (location=2) in vec2 tex_coord;

out vec3 v_normal;
out vec3 v_frag_pos;
out vec2 v_tex_coord;

uniform mat4 u_camera;
uniform mat4 u_transform;

void main() {
	gl_Position = u_camera * u_transform * vec4(position,1.0);
	v_frag_pos = vec3(u_transform * vec4(position, 1.0));
	v_normal = mat3(transpose(inverse(u_transform))) * normal;
	v_tex_coord = tex_coord;
}