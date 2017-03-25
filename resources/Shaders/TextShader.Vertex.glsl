#version 330

layout (location = 0) in vec2 vp;
layout (location = 1) in vec2 tex;

uniform mat4 View = mat4(1.0f);
uniform vec2 TexSize;
uniform vec4 Colour = vec4(1.0f, 1.0f, 1.0f, 1.0f);

out vec2 texUV;
out vec3 col;

void main() {
	gl_Position = View * vec4(vp, 0.0, 1.0);
	texUV.x = tex.x / TexSize.x;
	texUV.y = (TexSize.y - tex.y) / TexSize.y;
	col = Colour.rgb;
}