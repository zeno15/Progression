#ifndef INCLUDED_TOWER_GAME_OBJECTS_PROJECTILES_BASIC_BULLET_HPP_
#define INCLUDED_TOWER_GAME_OBJECTS_PROJECTILES_BASIC_BULLET_HPP_

#include <Tower/GameObjects/ProjectileBase.hpp>

#include <Graphics/CircleShape.hpp>

namespace Tower {
	class BasicBullet : public ProjectileBase {
	public:
		BasicBullet(const System::Vector2f& _initialPosition, const System::Vector2f& _targetPosition);
		BasicBullet(const System::Vector2f& _initialPosition, Creep *_target);
		virtual ~BasicBullet(void);

		virtual void update(float _delta) override;
		virtual bool handleEvent(const System::Event& _event) override;
		virtual void render(const Window::Window& _window, Graphics::RenderData _renderData) const override;
	private:
		Graphics::CircleShape m_Bullet;
		System::Vector2f m_TargetPosition;
	};

}

#endif // INCLUDED_TOWER_GAME_OBJECTS_PROJECTILES_BASIC_BULLET_HPP_