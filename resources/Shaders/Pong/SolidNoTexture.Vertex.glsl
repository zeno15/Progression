#version 330

layout (location = 0) in vec2 in_Position;

uniform mat4 MVP = mat4(1.0f);
uniform vec4 Colour = vec4(1.0f, 0.0f, 1.0f, 1.0f);

out vec4 frag_Colour;

void main() {
	gl_Position = MVP * vec4(in_Position, 0.0, 1.0);
	frag_Colour = Colour;
}