#include <Tower/GameObjects/TowerBase.hpp>
#include <Tower/GameObjects/Creep.hpp>

#include <Tower/Managers/LevelManager.hpp>
#include <Tower/Managers/TowerManager.hpp>

#include <Tower/TowerDefinitions.hpp>

#include <Infrastructure/InstanceCollection.hpp>

#include <System/VectorMath.hpp>

#include <cassert>

namespace Tower {

	TowerBase::TowerBase(const System::Vector2u& _tileCoordinates) :
		m_Target(nullptr) {
		Infrastructure::InstanceCollection::getInstance<LevelManager>().getLevel().getTile(_tileCoordinates.x, _tileCoordinates.y).m_Tower = this;
	}
	TowerBase::~TowerBase(void) {

	}

	void TowerBase::findTarget(void) {
		auto target = Infrastructure::InstanceCollection::getInstance<TowerManager>().findTarget(this);

		setTarget(target);
	}
	void TowerBase::setTarget(Creep *_target) {
		m_Target = _target;
	}


	bool TowerBase::getIsAlive(void) const {
		return true;
	}

	bool TowerBase::isTargetStillInRange(void) {
		assert(m_Target != nullptr);

		return System::distance(m_Target->position, position) <= m_Range;
	}
}