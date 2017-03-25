#ifndef INCLUDED_SYSTEM_MOUSE_HPP_
#define INCLUDED_SYSTEM_MOUSE_HPP_

#include <System/Vector2.hpp>

namespace Window {
	class Window;
}

namespace System {


	////////////////////////////////////////////////////////////
	//
	//	Class to give simple real time access to mouse position
	//	and state
	//
	////////////////////////////////////////////////////////////
	class Mouse {
	public:
		////////////////////////////////////////////////////////////
		//
		//	Enumeration of mouse buttons
		//
		////////////////////////////////////////////////////////////
		enum Button {
			Left,
			Right,
			Middle,
			Extra1,
			Extra2,
			NUM_BUTTONS
		};

		////////////////////////////////////////////////////////////
		//
		//	Returns whether or not a given mouse button is down
		//
		////////////////////////////////////////////////////////////
		static bool isButtonDown(Button _button);

		////////////////////////////////////////////////////////////
		//
		//	Gets the position of the mouse cursor in desktop
		//	coordinates
		//
		////////////////////////////////////////////////////////////
		static Vector2i getPosition(void);
		////////////////////////////////////////////////////////////
		//
		//	Gets the position of the mouse cursor relative to the 
		//	given window
		//
		////////////////////////////////////////////////////////////
		static Vector2i getPosition(const Window::Window& _relative);

		////////////////////////////////////////////////////////////
		//
		//	Sets the mouses position in desktop coordinates
		//
		////////////////////////////////////////////////////////////
		static void setPosition(const Vector2<int>& _position);

		////////////////////////////////////////////////////////////
		//
		//	Sets the mouses position relative to the given window
		//
		////////////////////////////////////////////////////////////
		static void setPosition(const Vector2<int>& _position, const Window::Window& _window);
	};

}
#endif // INCLUDED_SYSTEM_MOUSE_HPP_