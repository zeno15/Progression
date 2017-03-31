#ifndef INCLUDED_DRILLER_ELEMENTS_ELEMENT_HELPERS_HPP_
#define INCLUDED_DRILLER_ELEMENTS_ELEMENT_HELPERS_HPP_

#include <vector>

#include <System/Vector2.hpp>

////////////////////////////////////////////////////////////
///
///	\namespace Driller
///
////////////////////////////////////////////////////////////
namespace Driller {
	////////////////////////////////////////////////////////////
	///
	///	\brief	Misc helping methods for elements
	///
	////////////////////////////////////////////////////////////
	class ElementHelpers {
	public:
		static std::vector<float> createVerticiesForStaticTexture(const System::Vector2f& _textureId);
		static void createBasicDoubleTriQuadForTextureId(const System::Vector2f& _textureId, unsigned int *m_VAO, unsigned int *_m_VBO);
	};
}

#endif // INCLUDED_DRILLER_ELEMENTS_ELEMENT_HELPERS_HPP_