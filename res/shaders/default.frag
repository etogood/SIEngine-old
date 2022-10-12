#version 330
out vec4 frag_color;

in vec3 normal;
in vec3 frag_pos;
in vec2 tex_coords;
in vec2 spec_map_coords;

uniform vec3 view_pos;

struct Material{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};
uniform Material material;

struct DirLight{
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform DirLight dir_light;
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 view_dir);

struct PointLight{
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
#define NR_POINT_LIGHTS 2
uniform PointLight point_lights[NR_POINT_LIGHTS];
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 frag_pos, vec3 view_dir);

struct SpotLight{
    vec3 position;
    vec3 direction;
    float cut_off;
    float outer_cut_off;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform SpotLight spot_light;
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 frag_pos, vec3 view_dir);

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 view_dir){
    vec3 light_dir = normalize(-light.direction);
    float diff     = max(dot(normal, light_dir), 0.0);

    vec3 reflect_dir = reflect(-light_dir, normal);
    float spec       = pow(max(dot(view_dir, reflect_dir), 0.0), material.shininess);

    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, tex_coords));
    vec3 diffuse  = light.diffuse  * vec3(texture(material.diffuse, tex_coords)) * diff;
    vec3 specular = light.specular * vec3(texture(material.diffuse, tex_coords)) * spec;
    return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 frag_pos, vec3 view_dir){
    vec3 light_dir = normalize(light.position - frag_pos);
    float diff     = max(dot(normal, light_dir), 0.0);

    vec3 reflect_dir = reflect(-light_dir, normal);
    float spec       = pow(max(dot(view_dir, reflect_dir), 0.0), material.shininess);

    float distance    = length(light.position - frag_pos);
    float attenuation = 1.0 / (light.constant + light.linear * distance
                            + light.quadratic * (distance * distance));

    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, tex_coords));
    vec3 diffuse  = light.diffuse  * vec3(texture(material.diffuse, tex_coords)) * diff;
    vec3 specular = light.specular * vec3(texture(material.diffuse, tex_coords)) * spec;

    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 frag_pos, vec3 view_dir){
    vec3 light_dir = normalize(light.position - frag_pos);
    float diff     = max(dot(normal, light_dir), 0.0);

    vec3 reflect_dir = reflect(-light_dir, normal);
    float spec       = pow(max(dot(view_dir, reflect_dir), 0.0), material.shininess);

    float distance    = length(light.position - frag_pos);
    float attenuation = 1.0 / light.constant + light.linear * distance + light.quadratic * (distance * distance);

    float theta     = dot(light_dir, normalize(-light.direction));
    float epsilon   = light.cut_off - light.outer_cut_off;
    float intensity = clamp((theta - light.outer_cut_off) / epsilon, 0.0, 1.0);

    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, tex_coords));
    vec3 diffuse  = light.diffuse  * vec3(texture(material.diffuse, tex_coords)) * diff;
    vec3 specular = light.specular * vec3(texture(material.diffuse, tex_coords)) * spec;

    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);
}

void main(){
    vec3 norm = normalize(normal);
    vec3 view_dir = normalize(view_pos - frag_pos);
    vec3 result;

    result += CalcDirLight(dir_light, norm, view_dir);

    for (int i = 0; i < NR_POINT_LIGHTS; i++)
        result += CalcPointLight(point_lights[i], norm, frag_pos, view_dir);

    frag_color = vec4(result, 1.0);
}
