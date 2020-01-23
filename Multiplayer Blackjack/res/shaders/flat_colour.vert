#version 330 core

layout (location=0) in vec3 position;
layout (location=1) in vec3 normal;

out vec3 v_normal;
out vec3 v_frag_pos;

uniform mat4 u_camera;
uniform mat4 u_transform;

void main() {
	gl_Position = u_camera * u_transform * vec4(position,1.0);
	v_frag_pos = vec3(u_transform * vec4(position, 1.0));
	v_normal = mat3(transpose(inverse(u_transform))) * normal;
}