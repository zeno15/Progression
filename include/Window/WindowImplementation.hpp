#ifndef INCLUDED_WINDOW_WINDOW_IMPLEMENTATION_HPP_
#define INCLUDED_WINDOW_WINDOW_IMPLEMENTATION_HPP_

#ifdef _WIN32
	#include <Windows.h>
	#include <Window/WindowImplementationWin32.hpp>
	#include <Window/OpenGLDefinitionsWindows.hpp>

namespace Window {
	typedef WindowImplementationWin32 WindowImplementation;
	typedef HWND WindowHandle;
}

#endif
#ifdef __linux__
#endif 

#endif // INCLUDED_WINDOW_WINDOW_IMPLEMENTATION_HPP_