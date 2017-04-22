#include <Tower/Managers/ProjectileManager.hpp>

#include <Tower/GameObjects/Creep.hpp>

namespace Tower {
	const std::string ProjectileManager::Name = "ProjectileManager";

	void ProjectileManager::update(float _delta) {
		for (unsigned int iProj = 0; iProj < m_Projectiles.size(); iProj += 1) {
			m_Projectiles[iProj]->update(_delta);

			if (!m_Projectiles[iProj]->getIsAlive()) {
				m_Projectiles.erase(m_Projectiles.begin() + iProj);
				iProj -= 1;
			}
		}
	}
	bool ProjectileManager::handleEvent(const System::Event& _event) {
		for (auto& proj : m_Projectiles) {
			if (proj->handleEvent(_event)) {
				return true;
			}
		}
		return false;
	}
	void ProjectileManager::render(const Window::Window& _window, Graphics::RenderData _renderData) const {
		for (auto& proj : m_Projectiles) {
			proj->render(_window, _renderData);
		}
	}

	void ProjectileManager::addProjectile(ProjectileBase *_projectile) {
		m_Projectiles.push_back(_projectile);
	}

	void ProjectileManager::onCreepReachedEnd(Creep *_creep) {
		for (auto& proj : m_Projectiles) {
			if (proj->m_Target == _creep) {
				proj->m_Target = nullptr;
			}
		}
	}
	void ProjectileManager::onCreepKilled(Creep *_creep) {

	}
}