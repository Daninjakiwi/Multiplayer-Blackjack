#version 330 core

out vec4 colour;

in vec3 v_normal;
in vec3 v_frag_pos;
in vec2 v_tex_coord;

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	sampler2D t_diffuse;
	sampler2D t_specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform vec3 u_view_pos;
uniform Material u_material;
uniform Light u_light;

uniform bool u_enable_diffuse;
uniform bool u_enable_specular;

void main() {
    // ambient
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	
	// diffuse 
    vec3 norm = normalize(v_normal);
	
    vec3 lightDir = normalize(u_light.position - v_frag_pos);
    float diff = max(dot(norm, lightDir), 0.0);
	
	// specular
    vec3 viewDir = normalize(u_view_pos - v_frag_pos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_material.shininess);
	
	if (u_enable_diffuse) {
		ambient = u_light.ambient * texture(u_material.t_diffuse, v_tex_coord).rgb;
		diffuse = u_light.diffuse * diff * texture(u_material.t_diffuse, v_tex_coord).rgb;  
	} else {
		ambient = u_light.ambient * u_material.ambient;
		diffuse = u_light.diffuse * diff * u_material.diffuse;
	}
  	
	if (u_enable_specular) {
		specular = u_light.specular * spec * texture(u_material.t_specular, v_tex_coord).rgb;  
	} else {
		specular = u_light.specular * spec * u_material.specular;
	}

    vec3 result = ambient + diffuse + specular;
    colour = vec4(result, 1.0);
}