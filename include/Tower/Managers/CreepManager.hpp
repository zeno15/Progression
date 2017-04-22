#ifndef INCLUDED_TOWER_MANAGERS_CREEP_MANAGER_HPP_
#define INCLUDED_TOWER_MANAGERS_CREEP_MANAGER_HPP_

#include <Infrastructure/Manager.hpp>

#include <Tower/GameObjects/Creep.hpp>

#include <Tower/Components/Tile.hpp>

#include <vector>

namespace Tower {
	class CreepManager : public Infrastructure::Manager {
	public:
		friend class InstanceCollection;

		const static std::string Name;		///<	The name of the manager

		void update(float _delta);
		bool handleEvent(const System::Event& _event);
		void render(const Window::Window& _window, Graphics::RenderData _renderData) const;

		void addCreep(Creep *_creep, Tile *_startingTile);

		std::vector<Creep *>& getCreeps(void);

	private:
		std::vector<Creep *> m_Creeps;
	};
}

#endif // INCLUDED_TOWER_MANAGERS_CREEP_MANAGER_HPP_