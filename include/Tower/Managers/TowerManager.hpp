#ifndef INCLUDED_TOWER_MANAGERS_TOWER_MANAGER_HPP_
#define INCLUDED_TOWER_MANAGERS_TOWER_MANAGER_HPP_

#include <Infrastructure/Manager.hpp>

#include <Tower/GameObjects/TowerBase.hpp>

#include <vector>

namespace Tower {
	class Creep;
	class TowerManager : public Infrastructure::Manager {
	public:
		friend class InstanceCollection;

		const static std::string Name;		///<	The name of the manager

		void update(float _delta);
		bool handleEvent(const System::Event& _event);
		void render(const Window::Window& _window, Graphics::RenderData _renderData) const;

		void onCreepReachedEnd(Creep *_creep);
		void onCreepKilled(Creep *_creep);

		void addTower(TowerBase *_tower);

		Creep *findTarget(TowerBase *_tower);

	private:
		std::vector<TowerBase *> m_Towers;
	};
}

#endif // INCLUDED_TOWER_MANAGERS_TOWER_MANAGER_HPP_