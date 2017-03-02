#include <ECS/Component.hpp>

namespace ECS {

	Component::Component(unsigned int _entityId) :
		m_EntityId(_entityId) {
	}

	Component::~Component() {
	}


	unsigned int Component::getEntityId(void) const {
		return m_EntityId;
	}

}