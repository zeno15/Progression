#include <System/Mouse.hpp>

#include <System/InputImplementation.hpp>

#include <Window/Window.hpp>

namespace System {

	bool Mouse::isButtonDown(Button _button) {
		return InputImplementation::isMouseButtonDown(_button);
	}

	Vector2i Mouse::getPosition(void) {
		return InputImplementation::getMousePosition();
	}
	Vector2i Mouse::getPosition(const Window::Window& _relative) {
		return InputImplementation::getMousePosition(_relative);
	}

	void Mouse::setPosition(const Vector2<int>& _position) {
		InputImplementation::setMousePosition(_position);
	}
	void Mouse::setPosition(const Vector2<int>& _position, const Window::Window& _window) {
		InputImplementation::setMousePosition(_position, _window);
	}

}