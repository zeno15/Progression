#include <Driller/Components/TransformationComponent.hpp>

namespace Driller {
	TransformationComponent::TransformationComponent(unsigned int _entityId) :
		TransformationComponent(_entityId, System::Vector2f()) {

	}
	TransformationComponent::TransformationComponent(unsigned int _entityId, const System::Vector2f& _position) :
		TransformationComponent(_entityId, _position, System::Vector2f()) {

	}
	TransformationComponent::TransformationComponent(unsigned int _entityId, const System::Vector2f& _position, const System::Vector2f& _size) :
		ECS::Component(_entityId),
		position(_position),
		size(_size) {

	}
}