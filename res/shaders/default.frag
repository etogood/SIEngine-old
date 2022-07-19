#version 330

struct Material{
        sampler2D diffuse;
        sampler2D specular;
        float shininess;
};

struct Light{
        vec3 position;

        vec3 ambient;
        vec3 diffuse;
        vec3 specular;
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
    float diff = max(dot(norm, light_dir), 0.0);
    vec3 view_dir = normalize(view_pos - frag_pos);
    vec3 reflect_dir = reflect(-light_dir, norm);
    float spec = pow(max(dot(view_dir, reflect_dir), 0.0), material.shininess);

    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, tex_coords));
    vec3 diffuse  = light.diffuse  * vec3(texture(material.diffuse, tex_coords))       * diff;
    vec3 specular = light.specular * vec3(texture(material.specular, spec_map_coords)) * spec;

    frag_color = vec4(ambient + diffuse + specular, 1.0);
}