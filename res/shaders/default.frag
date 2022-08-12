#version 330

struct Material{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light{
    vec3 position;
    vec3 direction;

    float outer_cut_off;
    float cut_off;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

uniform Material material;
uniform Light light;

in vec3 normal;
in vec3 frag_pos;
in vec2 tex_coords;
in vec2 spec_map_coords;

out vec4 frag_color;

uniform vec3 view_pos;

void main(){
    vec3 norm = normalize(normal);
    vec3 light_dir = normalize(light.position - frag_pos);
    vec3 view_dir = normalize(view_pos - frag_pos);
    vec3 reflect_dir = reflect(-light_dir, norm);
    
    float diff = max(dot(norm, light_dir), 0.0);
    float spec = pow(max(dot(view_dir, reflect_dir), 0.0), material.shininess);

    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, tex_coords));
    vec3 diffuse  = light.diffuse  * vec3(texture(material.diffuse, tex_coords))       * diff;
    vec3 specular = light.specular * vec3(texture(material.specular, spec_map_coords)) * spec;

    float theta = dot(light_dir, normalize(-light.direction));
    float epsilon = light.cut_off - light.outer_cut_off;
    float intensity = clamp((theta - light.outer_cut_off) / epsilon, 0.0, 1.0);
    diffuse *= intensity;
    specular *= intensity;

    float distance = length(light.position - frag_pos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    vec3 result = ambient + diffuse + specular;
    frag_color = vec4(result, 1.0);
}