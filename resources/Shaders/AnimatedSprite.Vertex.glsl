#version 330

layout (location = 0) in vec2 in_Position;
layout (location = 1) in vec2 in_TexUV;

uniform mat4 MVP = mat4(1.0f);
uniform vec4 Colour = vec4(1.0f, 1.0f, 1.0f, 1.0f);

out vec2 texUV;
out vec4 colour;

void main() {
	gl_Position = MVP * vec4(in_Position, 0.0, 1.0);
	texUV = in_TexUV;
	colour = Colour;
}