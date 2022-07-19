#version 330

struct Material{
        vec3 ambient;
        vec3 diffuse;
        vec3 specular;
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

out vec4 frag_color;

uniform vec3 view_pos;

void main(){
    vec3 norm = normalize(normal);

    vec3 ambient = material.ambient * light.ambient;

    vec3 light_dir = normalize(light.position - frag_pos);
    float diff = max(dot(norm, light_dir), 0.0);

    vec3 diffuse = (diff * material.diffuse) * light.diffuse;

    vec3 view_dir = normalize(view_pos - frag_pos);
    vec3 reflect_dir = reflect(-light_dir, norm);
    float spec = pow(max(dot(view_dir, reflect_dir), 0.0), material.shininess);

    vec3 specular = (material.specular * spec) * light.specular;

    vec3 result = ambient + diffuse + specular;
    frag_color = vec4(result, 1.0);
}