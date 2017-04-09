#ifndef INCLUDED_DRILLER_ELEMENTS_ELEMENT_HELPERS_HPP_
#define INCLUDED_DRILLER_ELEMENTS_ELEMENT_HELPERS_HPP_

#include <vector>

#include <System/Vector2.hpp>

#include <Driller/Elements/JobElement.hpp>

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

		static JobElement *createBuildElevatorJob(int _level);
		static JobElement *createDigDirtJob(int _level, int _column);
		static JobElement *createBuildRoomJob(const JobContextInfo& _contextInfo);

		static JobElement *createJobForRoom(DrillerDefinitions::RoomType _roomType, const System::Vector2i& _tileCoordinates, const System::Vector2f& _workPosition);
	};
}

#endif // INCLUDED_DRILLER_ELEMENTS_ELEMENT_HELPERS_HPP_