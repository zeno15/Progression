#version 330

in vec2 texUV;
in vec4 colour;

uniform sampler2D tex;
out vec4 out_FragColour;

void main() {
	out_FragColour = texture(tex, texUV) * colour;
}