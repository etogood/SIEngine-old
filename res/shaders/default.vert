#version 330
layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec2 texture_coords;
layout(location = 2) in vec2 specular_map_coords;

out vec2 tex_coords;
out vec2 spec_map_coords;
out vec3 normal;
out vec3 frag_pos;

uniform mat4 mvp;
uniform mat4 model;

void main() {
   tex_coords = texture_coords;
   spec_map_coords = specular_map_coords;
   normal = mat3(transpose(inverse(model))) * vertex_position;
   frag_pos = vec3(model * vec4(vertex_position, 1.0));
   gl_Position = mvp * vec4(vertex_position, 1.0);
}