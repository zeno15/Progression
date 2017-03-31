#include <Pong/PongResources.hpp>

namespace Pong {
	const std::string PongResources::DefaultFontName = "Arial";
	const std::string PongResources::DefaultFontFilename = "C:/Windows/Fonts/arial.ttf";

	const std::string PongResources::SolidNoTextureShaderName = "SolidNoTexture";
	const std::string PongResources::SolidNoTextureShaderVertexPath = "C:/Users/markd/Documents/Git/Progression/resources/Shaders/Pong/SolidNoTexture.Vertex.glsl";
	const std::string PongResources::SolidNoTextureShaderFragmentPath = "C:/Users/markd/Documents/Git/Progression/resources/Shaders/Pong/SolidNoTexture.Fragment.glsl";
	const std::string PongResources::SolidNoTextureShaderUniformMVP = "MVP";
	const std::string PongResources::SolidNoTextureShaderUniformColour = "Colour";

	const std::string PongResources::TextShaderName = "TextShader";
	const std::string PongResources::TextShaderVertexPath = "C:/Users/markd/Documents/Git/Progression/resources/Shaders/TextShader.Vertex.glsl";
	const std::string PongResources::TextShaderFragmentPath = "C:/Users/markd/Documents/Git/Progression/resources/Shaders/TextShader.Fragment.glsl";
	const std::string PongResources::TextShaderUniformView = "View";
	const std::string PongResources::TextShaderUniformTexSize = "TexSize";
	const std::string PongResources::TextShaderUniformColour = "Colour";
}