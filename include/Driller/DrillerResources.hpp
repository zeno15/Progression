#ifndef INCLUDED_DRILLER_DRILLER_RESOURCES_HPP_
#define INCLUDED_DRILLER_DRILLER_RESOURCES_HPP_

#include <string>

#include <System/Vector2.hpp>

////////////////////////////////////////////////////////////
///
///	\namespace Driller
///
////////////////////////////////////////////////////////////
namespace Driller {
	////////////////////////////////////////////////////////////
	///
	///	\brief	Resources for Driller
	///
	////////////////////////////////////////////////////////////
	class DrillerResources {
	public:
		static const std::string				DefaultFontName;								///<	The font manager registered name for the default font
		static const std::string				DefaultFontFilename;							///<	The path to the default font

		static const std::string				StaticTexturedShaderName;						///<	Name of the static textured shader
		static const std::string				StaticTexturedShaderVertexFilename;				///<	Filename of the static textured vertex file
		static const std::string				StaticTexturedShaderFragmentFilename;			///<	Filename of the static textured fragment file
		static const std::string				StaticTexturedShaderMVPUniformName;				///<	Name of MVP uniform matrix

		static const std::string				BuildingGhostShaderName;						///<	
		static const std::string				BuildingGhostShaderVertexFilename;				///<	
		static const std::string				BuildingGhostShaderFragmentFilename;			///<	
		static const std::string				BuildingGhostShaderMVPUniformName;				///<	
		static const std::string				BuildingGhostShaderColourUniformName;			///<

		static const std::string				AnimatedSpriteShader;							///<	
		static const std::string				AnimatedSpriteShaderVertexFilename;				///<	
		static const std::string				AnimatedSpriteShaderFragmentFilename;			///<	
		static const std::string				AnimatedSpriteShaderMVPUniformName;				///<	
		static const std::string				AnimatedSpriteShaderColourUniformName;			///<	
		

		static const std::string				SpriteSheetName;								///<	The texture manager registered name for the sprite sheet
		static const std::string				SpriteSheetFilename;							///<	The path to the spritesheet
		static const System::Vector2f			SpriteSheetSize;								///<	The size of the spriteSheet
		static const System::Vector2f			ElevatorStaticSpriteIndex;						///<	Index of the elevator sprite
		static const System::Vector2f			DirtStaticSpriteIndex;							///<	Index of the dirt sprite
		static const System::Vector2f			EmptyDirtStaticSpriteIndex;						///<	Index of the mined out dirt sprite
		static const System::Vector2f			WorkerSpriteIndex;								///<	Index of the worker sprite
		static const System::Vector2f			JobPendingSpriteIndex;							///<	Index of the job pending sprite

		static const System::Vector2u			DormSpritePosition;								///<	Position of bottom left tile of dorm sprite
		static const System::Vector2u			DormSpriteSize;									///<	Size of dorm sprite in tiles
		static const System::Vector2u			MiningSpritePosition;							///<	Position of bottom left tile of mining sprite
		static const System::Vector2u			MiningSpriteSize;								///<	Size of mining sprite in tiles

		static const std::string				TestShaderName;									///<	Name of the test shader
		static const std::string				TestShaderVertexFilename;						///<	Filename of the test shader vertex file
		static const std::string				TestShaderFragmentFilename;						///<	Filename of the test shader fragment file

		static const std::string				TestShaderMVPUniformName;						///<	Name of MVP uniform matrix
		static const std::string				TestShaderColourUniformName;					///<	Name of Colour uniform
	};
}

#endif // INCLUDED_DRILLER_DRILLER_RESOURCES_HPP_