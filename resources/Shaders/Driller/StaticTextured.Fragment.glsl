#version 330

in vec2 texUV;

uniform sampler2D tex;

void main() {
	gl_FragColor = texture(tex, texUV);
}