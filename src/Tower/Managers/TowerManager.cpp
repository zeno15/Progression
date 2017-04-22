#include <Tower/Managers/TowerManager.hpp>

#include <Tower/Managers/CreepManager.hpp>

#include <Infrastructure/InstanceCollection.hpp>

#include <System/VectorMath.hpp>

namespace Tower {
	const std::string TowerManager::Name = "TowerManager";

	void TowerManager::update(float _delta) {

		for (unsigned int iTower = 0; iTower < m_Towers.size(); iTower += 1) {
			m_Towers[iTower]->update(_delta);

			if (!m_Towers[iTower]->getIsAlive()) {
				m_Towers.erase(m_Towers.begin() + iTower);
				iTower -= 1;
			}
		}
	}
	bool TowerManager::handleEvent(const System::Event& _event) {
		for (auto& tower : m_Towers) {
			if (tower->handleEvent(_event)) {
				return true;
			}
		}

		return false;
	}
	void TowerManager::render(const Window::Window& _window, Graphics::RenderData _renderData) const {
		for (auto& tower : m_Towers) {
			tower->render(_window, _renderData);
		}
	}

	void TowerManager::onCreepReachedEnd(Creep *_creep) {
		for (auto& tower : m_Towers) {
			if (tower->m_Target == _creep) {
				tower->setTarget(nullptr);
			}
		}
	}
	void TowerManager::onCreepKilled(Creep *_creep) {
		for (auto& tower : m_Towers) {
			if (tower->m_Target == _creep) {
				tower->setTarget(nullptr);
			}
		}
	}

	void TowerManager::addTower(TowerBase *_tower) {
		m_Towers.push_back(_tower);
	}

	Creep *TowerManager::findTarget(TowerBase *_tower) {
		auto& creepManager = Infrastructure::InstanceCollection::getInstance<CreepManager>();

		for (auto creep : creepManager.getCreeps()) {
			if (_tower->m_Range >= System::distance(creep->position, _tower->position)) {
				return creep;
			}
		}

		return nullptr;
	}
}