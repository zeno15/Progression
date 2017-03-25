#ifndef INCLUDED_GRAPHICS_GLYPH_HPP_
#define INCLUDED_GRAPHICS_GLYPH_HPP_

#include <string>

////////////////////////////////////////////////////////////
///
///	\namespace	Graphics
///
////////////////////////////////////////////////////////////
namespace Graphics {
	////////////////////////////////////////////////////////////
	///
	///	\brief	Class to encapsulate a font glyph
	///
	////////////////////////////////////////////////////////////
	class Glyph {
	public:
		int character;

		unsigned int width;
		unsigned int height;

		unsigned int textureX;
		unsigned int textureY;
	};
}

#endif // INCLUDED_GRAPHICS_GLYPH_HPP_