#ifndef INLCLUDED_TOWER_GAME_OBJECTS_TOWERS_BASIC_TOWER_HPP_
#define INLCLUDED_TOWER_GAME_OBJECTS_TOWERS_BASIC_TOWER_HPP_

#include <Tower/GameObjects/TowerBase.hpp>

#include <Graphics/CircleShape.hpp>

namespace Tower {

	class BasicTower : public TowerBase {
	public:
		BasicTower(const System::Vector2u& _tilePosition);
		virtual ~BasicTower(void);

		virtual void update(float _delta) override;
		virtual bool handleEvent(const System::Event& _event) override;
		virtual void render(const Window::Window& _window, Graphics::RenderData _renderData) const override;

	private:
		Graphics::CircleShape m_Body;
		Graphics::CircleShape m_Turret;
		float m_Angle;
		float m_CooldownTime;
	};
}

#endif // INLCLUDED_TOWER_GAME_OBJECTS_TOWERS_BASIC_TOWER_HPP_