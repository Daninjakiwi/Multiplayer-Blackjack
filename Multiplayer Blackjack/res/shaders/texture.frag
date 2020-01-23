#version 330 core

out vec4 colour;

in vec3 v_normal;
in vec3 v_frag_pos;
in vec2 v_tex_coord;

struct Material {
	sampler2D diffuse;
	sampler2D specular;
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

void main() {
	vec4 col = texture(u_material.diffuse, v_tex_coord);
	if (col.a < 0.1) {
		discard;
	}

    // ambient
    vec3 ambient = u_light.ambient * texture(u_material.diffuse, v_tex_coord).rgb;
  	
    // diffuse 
    vec3 norm = normalize(v_normal);
	
    vec3 lightDir = normalize(u_light.position - v_frag_pos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = u_light.diffuse * diff * texture(u_material.diffuse, v_tex_coord).rgb;  
    
    // specular
    vec3 viewDir = normalize(u_view_pos - v_frag_pos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_material.shininess);
    vec3 specular = u_light.specular * spec * 0.3;  
        
    vec3 result = ambient + diffuse + specular;
    colour = vec4(result, 1.0);
}