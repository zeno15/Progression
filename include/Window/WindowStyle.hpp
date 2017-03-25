#ifndef INCLUDED_WINDOW_WINDOW_STYLE_HPP_
#define INCLUDED_WINDOW_WINDOW_STYLE_HPP_

namespace Window {

	namespace WindowStyle {

		////////////////////////////////////////////////////////////
		///
		///	\brief	Enumerated description of window style
		///
		////////////////////////////////////////////////////////////
		enum {
			None = 0,								///<	No style i.e. splash screen
			Titlebar = 1 << 0,						///<	Window has title bar
			Resize = 1 << 1,						///<	Window is resizable
			Close = 1 << 2,							///<	Window has close button
			Fullscreen = 1 << 3,					///<	Window is fullscreen

			Default = Titlebar | Resize | Close		///<	Titlebar, resizable and closeable
		};

	}

}

#endif // INCLUDED_WINDOW_WINDOW_STYLE_HPP_