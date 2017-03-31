#version 330

in vec2 texUV;
in vec4 colour;

uniform sampler2D tex;

void main() {
	gl_FragColor = texture(tex, texUV) * colour;
}