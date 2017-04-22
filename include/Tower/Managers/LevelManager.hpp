#ifndef INCLUDED_TOWER_MANAGERS_LEVEL_MANAGER_HPP_
#define INCLUDED_TOWER_MANAGERS_LEVEL_MANAGER_HPP_

#include <Infrastructure/Manager.hpp>

#include <Tower/GameObjects/Level.hpp>

namespace Tower {
	class Creep;

	class LevelManager : public Infrastructure::Manager {
	public:
		friend class InstanceCollection;

		const static std::string Name;		///<	The name of the manager

		LevelManager(void);
		~LevelManager(void);


		void update(float _delta);
		bool handleEvent(const System::Event& _event);
		void render(const Window::Window& _window, Graphics::RenderData _renderData) const;

		void createNewLevel(void);
		void loadLevel(const std::string& _level);
		Level& getLevel(void);
		bool hasLevel(void) const;

		void onCreepReachedEnd(Creep *_creep);
		void onCreepKilled(Creep *_creep);

	private:
		Level * m_CurrentLevel;
	};
}

#endif // INCLUDED_TOWER_MANAGERS_LEVEL_MANAGER_HPP_