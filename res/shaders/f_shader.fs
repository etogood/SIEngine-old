#version 330

in vec2 texCoords;

out vec4 frag_color;

uniform sampler2D tex;

void main() {
    frag_color = texture(tex, texCoords);
}