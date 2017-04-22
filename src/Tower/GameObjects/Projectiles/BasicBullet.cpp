#include <Tower/GameObjects/Projectiles/BasicBullet.hpp>
#include <Tower/GameObjects/Creep.hpp>

#include <Tower/TowerDefinitions.hpp>

#include <System/VectorMath.hpp>

#define SPEED 512.0f

namespace Tower {

	BasicBullet::BasicBullet(const System::Vector2f& _initialPosition, const System::Vector2f& _targetPosition) :
		BasicBullet(_initialPosition, nullptr) {
		m_TargetPosition = _targetPosition;
	}
	BasicBullet::BasicBullet(const System::Vector2f& _initialPosition, Creep *_target) :
		m_Bullet(2.0f) {
		position = _initialPosition;
		m_Target = _target;
	}


	BasicBullet::~BasicBullet(void) {

	}

	void BasicBullet::update(float _delta) {
		if (m_Target != nullptr) {
			m_TargetPosition = m_Target->position;
		}
		auto distance = System::distance(position, m_TargetPosition);

		auto movement = _delta * SPEED;

		if (distance < movement) {
			position = m_TargetPosition;
			if (m_Target != nullptr) {
				m_Target->damage(1.2f);
			}
			m_Alive = false;
		}
		else {
			auto dir = System::normalise(m_TargetPosition - position);
			position += dir * _delta * SPEED;
		}
	}
	bool BasicBullet::handleEvent(const System::Event& _event) {
		return false;
	}
	void BasicBullet::render(const Window::Window& _window, Graphics::RenderData _renderData) const {
		_renderData.model.translate(System::Vector3f(position, TowerDefinitions::ProjectileZ));

		m_Bullet.render(_window, _renderData);
	}
}