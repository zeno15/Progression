#ifndef INCLUDED_TOWER_MANAGERS_PROJECTILE_MANAGER_HPP_
#define INCLUDED_TOWER_MANAGERS_PROJECTILE_MANAGER_HPP_

#include <Infrastructure/Manager.hpp>

#include <Tower/GameObjects/ProjectileBase.hpp>

#include <vector>

namespace Tower {
	class Creep;

	class ProjectileManager : public Infrastructure::Manager {
	public:
		friend class InstanceCollection;

		const static std::string Name;		///<	The name of the manager

		void update(float _delta);
		bool handleEvent(const System::Event& _event);
		void render(const Window::Window& _window, Graphics::RenderData _renderData) const;

		void onCreepReachedEnd(Creep *_creep);
		void onCreepKilled(Creep *_creep);

		void addProjectile(ProjectileBase *_projectile);

	private:
		std::vector<ProjectileBase *> m_Projectiles;
	};
}

#endif // INCLUDED_TOWER_MANAGERS_PROJECTILE_MANAGER_HPP_