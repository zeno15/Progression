#include <Infrastructure/Camera.hpp>

#include <System/Event.hpp>

namespace Infrastructure {
	const std::string Camera::Name = "Camera";

	Camera::Camera(void) :
		m_Zoom(1.0f) {

	}


	bool Camera::handleEvent(const System::Event& _event) {
		if (_event.type == System::Event::KeyDown) {
			if (_event.key.key == System::Keyboard::Left) {
				move(System::Vector2f(-20.0f, +0.0f));
				return true;
			}
			if (_event.key.key == System::Keyboard::Right) {
				move(System::Vector2f(+20.0f, +0.0f));
				return true;
			}
			if (_event.key.key == System::Keyboard::Up) {
				move(System::Vector2f(+0.0f, +20.0f));
				return true;
			}
			if (_event.key.key == System::Keyboard::Down) {
				move(System::Vector2f(+0.0f, -20.0f));
				return true;
			}
			if (_event.key.key == System::Keyboard::F1) {
				m_Position = System::Vector2f();
				m_Zoom = 1.0f;
				return true;
			}
		}

		if (_event.type == System::Event::MouseWheelChanged) {
			if (_event.wheel.delta > 0) {
				zoom(std::pow(1.1f, std::fabsf(static_cast<float>(_event.wheel.delta))));
				return true;
			}
			if (_event.wheel.delta < 0) {
				zoom(std::pow(1.0f / 1.1f, std::fabsf(static_cast<float>(_event.wheel.delta))));
				return true;
			}
		}

		return false;
	}

	void Camera::move(const System::Vector2f& _offset) {
		m_Position += _offset;
	}

	void Camera::setPosition(const System::Vector2f& _position) {
		m_Position = _position;
	}

	const System::Vector2f& Camera::getPosition(void) const {
		return m_Position;
	}


	void Camera::zoom(float _zoom) {
		m_Zoom *= _zoom;
	}

	void Camera::setZoom(float _zoom) {
		m_Zoom = _zoom;
	}

	const float Camera::getZoom(void) const {
		return m_Zoom;
	}
}