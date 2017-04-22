#version 330

layout (location = 0) in vec3 in_Position;
layout (location = 1) in vec4 in_Colour;

uniform mat4 MVP = mat4(1.0f);

out vec4 frag_Colour;

void main() {
	gl_Position = MVP * vec4(in_Position, 1.0);
	frag_Colour = in_Colour;
}