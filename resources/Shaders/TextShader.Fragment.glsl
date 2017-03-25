#version 330

in vec2 texUV;
in vec3 col;

uniform sampler2D tex;

out vec4 frag_colour;
void main() {
	frag_colour = vec4(col, texture(tex, texUV).r);
}