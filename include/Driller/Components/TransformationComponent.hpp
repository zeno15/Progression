#ifndef INCLUDED_DRILLER_COMPONENTS_TRANSFORMATION_COMPONENT_HPP_
#define INCLUDED_DRILLER_COMPONENTS_TRANSFORMATION_COMPONENT_HPP_

#include <ECS/Component.hpp>
#include <System/Vector2.hpp>

////////////////////////////////////////////////////////////
///
///	\namespace Driller
///
////////////////////////////////////////////////////////////
namespace Driller {

	////////////////////////////////////////////////////////////
	///
	///	\brief	Component to represent position and size
	///
	////////////////////////////////////////////////////////////
	class TransformationComponent : ECS::Component {
	public:
		////////////////////////////////////////////////////////////
		///
		///	\brief	Constructor
		///
		///	\param	The Entity id
		///
		////////////////////////////////////////////////////////////
		TransformationComponent(unsigned int _entityId);
		////////////////////////////////////////////////////////////
		///
		///	\brief	Constructor
		///
		///	\param	The Entity id
		///
		///	\param	The Position
		///
		////////////////////////////////////////////////////////////
		TransformationComponent(unsigned int _entityId, const System::Vector2f& _position);
		////////////////////////////////////////////////////////////
		///
		///	\brief	Constructor
		///
		///	\param	The Entity id
		///
		///	\param	The Position
		///
		///	\param	The Size
		///
		////////////////////////////////////////////////////////////
		TransformationComponent(unsigned int _entityId, const System::Vector2f& _position, const System::Vector2f& _size);

		System::Vector2f position;			///<	The position of the component
		System::Vector2f size;				///<	The size of the component
	};
}

#endif // INCLUDED_DRILLER_COMPONENTS_TRANSFORMATION_COMPONENT_HPP_