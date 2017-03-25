#ifndef INCLUDED_WINDOW_CONTEXT_IMPLEMENTATION_HPP_
#define INCLUDED_WINDOW_CONTEXT_IMPLEMENTATION_HPP_

#ifdef _WIN32
#include <Window/ContextWin32.hpp>
typedef Window::ContextWin32 ContextImplementation;
#endif
#ifdef __linux__
#endif 

#endif // INCLUDED_WINDOW_CONTEXT_IMPLEMENTATION_HPP_