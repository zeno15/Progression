#ifndef INCLUDED_TOWER_TOWER_RESOURCES_HPP_
#define INCLUDED_TOWER_TOWER_RESOURCES_HPP_

#include <string>

namespace Tower {
	////////////////////////////////////////////////////////////
	///
	///	\brief	Resources for Tower
	///
	////////////////////////////////////////////////////////////
	class TowerResources {
	public:
		static const std::string LevelDirectoryPath;

		static const std::string DefaultFontName;
		static const std::string DefaultFontFilename;

		static const std::string SolidNoTextureShaderName;
		static const std::string SolidNoTextureShaderVertexPath;
		static const std::string SolidNoTextureShaderFragmentPath;
		static const std::string SolidNoTextureShaderUniformMVP;
		static const std::string SolidNoTextureShaderUniformColour;

		static const std::string VertexArrayNoTextureShaderName;
		static const std::string VertexArrayNoTextureShaderVertexPath;
		static const std::string VertexArrayNoTextureShaderFragmentPath;
		static const std::string VertexArrayNoTextureShaderUniformMVP;

		static const std::string TextShaderName;
		static const std::string TextShaderVertexPath;
		static const std::string TextShaderFragmentPath;
		static const std::string TextShaderUniformView;
		static const std::string TextShaderUniformTexSize;
		static const std::string TextShaderUniformColour;
	};
}

#endif // INCLUDED_TOWER_TOWER_RESOURCES_HPP_