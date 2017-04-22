#ifndef INCLUDED_TOWER_GAME_OBJECTS_TOWER_HPP_
#define INCLUDED_TOWER_GAME_OBJECTS_TOWER_HPP_

#include <Tower/GameObjects/GameObject.hpp>

namespace Tower {
	class Creep;

	class TowerBase : public GameObject {
	public:
		TowerBase(const System::Vector2u& _tileCoordinates);
		virtual ~TowerBase(void);

		virtual void update(float _delta) = 0;
		virtual bool handleEvent(const System::Event& _event) = 0;
		virtual void render(const Window::Window& _window, Graphics::RenderData _renderData) const = 0;

		bool isTargetStillInRange(void);

		void findTarget(void);
		void setTarget(Creep *_target);


		bool getIsAlive(void) const;
		float m_Range;

		Creep *m_Target;
	};
}

#endif // INCLUDED_TOWER_GAME_OBJECTS_TOWER_HPP_