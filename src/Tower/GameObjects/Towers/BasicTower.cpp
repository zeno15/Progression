#include <Tower/GameObjects/Towers/BasicTower.hpp>
#include <Tower/GameObjects/Projectiles/BasicBullet.hpp>

#include <Tower/GameObjects/Creep.hpp>

#include <Tower/Managers/ProjectileManager.hpp>

#include <Tower/TowerDefinitions.hpp>

#include <Infrastructure/InstanceCollection.hpp>

#include <Graphics/CircleShape.hpp>

#include <System/VectorMath.hpp>

#include <cassert>

#define RADIUS (TowerDefinitions::TileSize / 2.0f - 4.0f)
#define COOLDOWN 1.0f

namespace Tower {
	BasicTower::BasicTower(const System::Vector2u& _tilePosition) :
		TowerBase(_tilePosition),
		m_Body(RADIUS),
		m_Turret(4.0f),
		m_Angle(0.0f),
		m_CooldownTime(0.0f) {


		position = System::Vector2f(_tilePosition) * TowerDefinitions::TileSize + System::Vector2f(TowerDefinitions::TileSize, TowerDefinitions::TileSize) / 2.0f;
		m_Body.setColour(Graphics::Colour::Yellow);
		m_Body.setTranslate(position);
		m_Turret.setColour(Graphics::Colour::Blue);
		m_Turret.setTranslate(position);

		m_Range = TowerDefinitions::TileSize * 4.0f;
	}
	BasicTower::~BasicTower(void) {
	}

	void BasicTower::update(float _delta) {
		m_CooldownTime -= _delta;

		if (m_Target == nullptr) {
			// Find target
			findTarget();
		}
		else {
			// Check target still in range
			if (!isTargetStillInRange()) {
				m_Target = nullptr;
			}
			else {
				// Point at target
				auto targetPosition = m_Target->position;
				auto dir = System::normalise(targetPosition - position);

				double angleInRadians = std::atan2(dir.y, dir.x);
				m_Angle = (angleInRadians / 3.14159265f) * 180.0;
				
				if (m_CooldownTime <= 0.0f) {
					m_CooldownTime = COOLDOWN;

					// Try and fire
					Infrastructure::InstanceCollection::getInstance<ProjectileManager>().addProjectile(new BasicBullet(position + System::Vector2f(std::cosf(m_Angle * 3.14159265f / 180.0f) * RADIUS, std::sinf(m_Angle * 3.14159265f / 180.0f) * RADIUS), m_Target));
				}
			}
		}
	}
	bool BasicTower::handleEvent(const System::Event& _event) {
		return false;
	}
	void BasicTower::render(const Window::Window& _window, Graphics::RenderData _renderData) const {
		_renderData.model.translate(System::Vector3f(0.0f, 0.0f, TowerDefinitions::TowerZ));

		m_Body.render(_window, _renderData);

		_renderData.model.translate(System::Vector3f(std::cosf(m_Angle * 3.14159265f / 180.0f) * RADIUS, std::sinf(m_Angle * 3.14159265f / 180.0f) * RADIUS, 0.1f));
		m_Turret.render(_window, _renderData);
	}
}