#include <Tower/Managers/CreepManager.hpp>

#include <Tower/TowerDefinitions.hpp>

#include <algorithm>

namespace Tower {
	const std::string CreepManager::Name = "CreepManager";

	void CreepManager::update(float _delta) {
		for (unsigned int iCreep = 0; iCreep < m_Creeps.size(); iCreep += 1) {
			m_Creeps[iCreep]->update(_delta);

			if (!m_Creeps[iCreep]->getIsAlive()) {
				m_Creeps.erase(m_Creeps.begin() + iCreep);
				iCreep -= 1;
			}
		}
	}
	bool CreepManager::handleEvent(const System::Event& _event) {
		for (unsigned int iCreep = 0; iCreep < m_Creeps.size(); iCreep += 1) {
			if (m_Creeps[iCreep]->handleEvent(_event)) {
				return true;
			}
		}

		return false;
	}
	void CreepManager::render(const Window::Window& _window, Graphics::RenderData _renderData) const {
		for (auto& creep : m_Creeps) {
			creep->render(_window, _renderData);
		}
	}

	void CreepManager::addCreep(Creep *_creep, Tile *_startingTile) {
		_creep->position = (System::Vector2f(_startingTile->x, _startingTile->y) + System::Vector2f(0.5f, 0.5f)) * TowerDefinitions::TileSize;
		_creep->setTile(_startingTile);
		m_Creeps.push_back(_creep);
	}

	std::vector<Creep *>& CreepManager::getCreeps(void) {
		return m_Creeps;
	}
}