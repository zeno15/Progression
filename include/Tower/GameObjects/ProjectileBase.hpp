#ifndef INCLUDED_TOWER_GAME_OBJECTS_PROJECTILE_BASE_HPP_
#define INCLUDED_TOWER_GAME_OBJECTS_PROJECTILE_BASE_HPP_

#include <Tower/GameObjects/GameObject.hpp>


namespace Tower {
	class Creep;
	class ProjectileBase : public GameObject {
	public:
		ProjectileBase(void);
		virtual ~ProjectileBase(void);

		virtual void update(float _delta) = 0;
		virtual bool handleEvent(const System::Event& _event) = 0;
		virtual void render(const Window::Window& _window, Graphics::RenderData _renderData) const = 0;

		bool getIsAlive(void) const;

		Creep *m_Target;

	protected:
		bool m_Alive;
	};
}

#endif // INCLUDED_TOWER_GAME_OBJECTS_PROJECTILE_BASE_HPP_