#include <Infrastructure/SceneManager.hpp>

#include <cassert>

namespace Infrastructure {

	const std::string SceneManager::Name = "SceneManager";

	SceneManager::SceneManager() {
		m_CurrentScene = nullptr;
	}

	SceneManager::~SceneManager() {}


	void SceneManager::update(float _delta) {
		if (m_CurrentScene != nullptr) {
			m_CurrentScene->update(_delta);
		}
	}
	bool SceneManager::handleEvent(const System::Event& _event) {
		if (m_CurrentScene != nullptr) {
			if (m_CurrentScene->handleEvent(_event)) {
				return true;
			}
		}

		return false;
	}

	void SceneManager::draw(Window::Window& _window, Graphics::RenderData _states) const {
		if (m_CurrentScene != nullptr) {
			m_CurrentScene->render(_window, _states);
		}
	}

	void SceneManager::addScene(Scene *_scene) {
		m_Scenes.push_back(_scene);
	}
	void SceneManager::removeScene(Scene *_scene) {
		for (unsigned int i = 0; i < m_Scenes.size(); i += 1) {
			if (m_Scenes[i] == _scene) {
				m_Scenes.erase(m_Scenes.begin() + i);
				return;
			}
		}
	}

	void SceneManager::setActiveScene(Scene *_scene) {
		m_CurrentScene = _scene;
	}
	Scene& SceneManager::getActiveScene(void) {
		assert(m_CurrentScene != nullptr);
		return *m_CurrentScene;
	}
	Scene& SceneManager::getScene(const std::string& _name) {
		for (auto& scene : m_Scenes) {
			if (scene->getName() == _name) {
				return *scene;
			}
		}

		throw std::runtime_error(std::string("Failed to find scene " + _name));
	}

}