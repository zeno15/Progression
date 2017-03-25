#include <System/Keyboard.hpp>
#include <System/InputImplementation.hpp>

namespace System {

	bool Keyboard::isKeyDown(Key _key) {
		return InputImplementation::isKeyDown(_key);
	}

}