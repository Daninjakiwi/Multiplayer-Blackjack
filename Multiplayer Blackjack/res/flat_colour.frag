#version 330 core

layout(location = 0) out vec4 colour;

in vec3 v_normal;
in vec3 v_frag_pos;

uniform vec3 u_colour;
uniform vec3 u_view_pos;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 
  
uniform Material u_material;

struct Light {
    vec3 position;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light u_light;

void main() {
    vec3 ambient = u_material.ambient * u_light.ambient;
	
	vec3 norm = normalize(v_normal);
	vec3 lightDir = normalize(u_light.position - v_frag_pos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = u_light.diffuse * (u_material.diffuse * diff);
	
	vec3 viewDir = normalize(u_view_pos - v_frag_pos);
	vec3 reflectDir = reflect(-lightDir, norm);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_material.shininess);
	vec3 specular = u_material.specular * spec * u_light.specular;  	
	
	vec3 result = ambient+diffuse+specular;

	colour = vec4(result,1.0);
}