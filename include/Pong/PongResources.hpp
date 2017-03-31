#ifndef INCLUDED_PONG_PONG_RESOURCES_HPP_
#define INCLUDED_PONG_PONG_RESOURCES_HPP_

#include <string>

namespace Pong {
	////////////////////////////////////////////////////////////
	///
	///	\brief	Resources for Pong
	///
	////////////////////////////////////////////////////////////
	class PongResources {
	public:
		static const std::string DefaultFontName;
		static const std::string DefaultFontFilename;

		static const std::string SolidNoTextureShaderName;
		static const std::string SolidNoTextureShaderVertexPath;
		static const std::string SolidNoTextureShaderFragmentPath;
		static const std::string SolidNoTextureShaderUniformMVP;
		static const std::string SolidNoTextureShaderUniformColour;

		static const std::string TextShaderName;
		static const std::string TextShaderVertexPath;
		static const std::string TextShaderFragmentPath;
		static const std::string TextShaderUniformView;
		static const std::string TextShaderUniformTexSize;
		static const std::string TextShaderUniformColour;
	};
}

#endif // INCLUDED_PONG_PONG_RESOURCES_HPP_