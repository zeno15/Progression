#include <Driller/DrillerResources.hpp>

namespace Driller {	
	const std::string DrillerResources::DefaultFontName = "Arial";
	const std::string DrillerResources::DefaultFontFilename = "C:/Windows/Fonts/arial.ttf";

	const std::string DrillerResources::StaticTexturedShaderName = "StaticTexturedShaderName";
	const std::string DrillerResources::StaticTexturedShaderVertexFilename = "C:/Users/markd/Documents/Git/Progression/resources/Shaders/Driller/StaticTextured.Vertex.glsl";
	const std::string DrillerResources::StaticTexturedShaderFragmentFilename = "C:/Users/markd/Documents/Git/Progression/resources/Shaders/Driller/StaticTextured.Fragment.glsl";
	const std::string DrillerResources::StaticTexturedShaderMVPUniformName = "MVP";


	const std::string DrillerResources::BuildingGhostShaderName = "BuildingGhostShaderName";
	const std::string DrillerResources::BuildingGhostShaderVertexFilename = "C:/Users/markd/Documents/Git/Progression/resources/Shaders/Driller/BuildingGhost.Vertex.glsl";
	const std::string DrillerResources::BuildingGhostShaderFragmentFilename = "C:/Users/markd/Documents/Git/Progression/resources/Shaders/Driller/BuildingGhost.Fragment.glsl";
	const std::string DrillerResources::BuildingGhostShaderMVPUniformName = "MVP";
	const std::string DrillerResources::BuildingGhostShaderColourUniformName = "Colour";


	const std::string DrillerResources::AnimatedSpriteShader = "AnimatedSpriteShader";
	const std::string DrillerResources::AnimatedSpriteShaderVertexFilename = "C:/Users/markd/Documents/Git/Progression/resources/Shaders/AnimatedSprite.Vertex.glsl";
	const std::string DrillerResources::AnimatedSpriteShaderFragmentFilename = "C:/Users/markd/Documents/Git/Progression/resources/Shaders/AnimatedSprite.Fragment.glsl";
	const std::string DrillerResources::AnimatedSpriteShaderMVPUniformName = "MVP";
	const std::string DrillerResources::AnimatedSpriteShaderColourUniformName = "Colour";

	const std::string DrillerResources::SpriteSheetName = "DrillerSpriteSheet";
	const std::string DrillerResources::SpriteSheetFilename = "C:/Users/markd/Documents/Git/Progression/resources/Textures/Driller/SpriteSheet.png";

	const System::Vector2f DrillerResources::SpriteSheetSize = System::Vector2f(2048.0f, 2048.0f);

	const System::Vector2f DrillerResources::ElevatorStaticSpriteIndex =	System::Vector2f(0.0f, 0.0f);
	const System::Vector2f DrillerResources::DirtStaticSpriteIndex =		System::Vector2f(1.0f, 0.0f);
	const System::Vector2f DrillerResources::EmptyDirtStaticSpriteIndex =	System::Vector2f(2.0f, 0.0f);
	const System::Vector2f DrillerResources::WorkerSpriteIndex =			System::Vector2f(1.0f, 1.0f);
	const System::Vector2f DrillerResources::JobPendingSpriteIndex =		System::Vector2f(0.0f, 2.0f);
	const System::Vector2f DrillerResources::ShuttleSpriteIndex =			System::Vector2f(4.0f, 1.0f);

	const System::Vector2u DrillerResources::DormSpritePosition =			System::Vector2u(0, 3);
	const System::Vector2u DrillerResources::DormSpriteSize =				System::Vector2u(2, 1);
	const System::Vector2u DrillerResources::MiningSpritePosition =			System::Vector2u(0, 4);
	const System::Vector2u DrillerResources::MiningSpriteSize =				System::Vector2u(3, 1);
	const System::Vector2u DrillerResources::ShuttleSpriteSize =			System::Vector2u(3, 2);

	const std::string DrillerResources::TestShaderName = "DrillerTestShaderName";
	const std::string DrillerResources::TestShaderVertexFilename = "C:/Users/markd/Documents/Git/Progression/resources/Shaders/Driller/BasicPosition.Vertex.glsl";
	const std::string DrillerResources::TestShaderFragmentFilename = "C:/Users/markd/Documents/Git/Progression/resources/Shaders/Driller/BasicPosition.Fragment.glsl";

	const std::string DrillerResources::TestShaderMVPUniformName = "MVP";
	const std::string DrillerResources::TestShaderColourUniformName = "Colour";
}