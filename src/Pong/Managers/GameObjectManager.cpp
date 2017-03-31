#include <Pong/Managers/GameObjectManager.hpp>

#include <Graphics/RenderData.hpp>

#include <Window/Window.hpp>

namespace Pong {
	const std::string GameObjectManager::Name = "GameObjectManager";

	void GameObjectManager::update(float _delta) {
		for (unsigned int i = 0; i < m_GameObjects.size(); i += 1) {
			m_GameObjects[i]->update(_delta);
		}

		if (m_GameObjectsToDelete.size() > 0) {
			for (unsigned int j = 0; j < m_GameObjectsToDelete.size(); j += 1) {
				for (unsigned int i = 0; i < m_GameObjects.size(); i += 1) {
					if (m_GameObjects[i] == m_GameObjectsToDelete[j]) {
						m_GameObjects.erase(m_GameObjects.begin() + i);
						return;
					}
				}
			}
			m_GameObjectsToDelete.clear();
		}
	}

	void GameObjectManager::render(const Window::Window& _window, Graphics::RenderData _RenderData) const {
		for (const auto& obj : m_GameObjects) {
			obj->render(_window, _RenderData);
		}
	}

	void GameObjectManager::addGameObject(GameObject *_obj) {
		m_GameObjects.push_back(_obj);
	}

	GameObject *GameObjectManager::getGameObject(const std::string& _name) {
		for (const auto obj : m_GameObjects) {
			if (obj->getName() == _name) {
				return obj;
			}
		}

		return nullptr;
	}

	void GameObjectManager::removeGameObject(GameObject *_object) {
		m_GameObjectsToDelete.push_back(_object);
	}
}