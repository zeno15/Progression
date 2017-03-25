#ifndef INCLUDED_SYSTEM_INPUT_IMPLEMENTATION_HPP_
#define INCLUDED_SYSTEM_INPUT_IMPLEMENTATION_HPP_

#ifdef _WIN32
#include <System/InputImplementationWin32.hpp>
namespace System {
	typedef InputImplementationWin32 InputImplementation;
}

#endif
#ifdef __linux__
#endif 

#endif // INCLUDED_SYSTEM_INPUT_IMPLEMENTATION_HPP_