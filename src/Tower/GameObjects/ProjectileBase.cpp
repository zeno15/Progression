#include <Tower/GameObjects/ProjectileBase.hpp>

namespace Tower {
	ProjectileBase::ProjectileBase(void) :
		m_Alive(true),
		m_Target(nullptr) {
	}
	ProjectileBase::~ProjectileBase(void) {
	}


	bool ProjectileBase::getIsAlive(void) const {
		return m_Alive;
	}
}