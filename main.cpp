#include <cstdlib>
#include <iostream>

#include <Driller/DrillerStart.hpp>
#include <Pong/PongStart.hpp>

#include <Window/Window.hpp>
#include <Window/OpenGL.hpp>
#include <Infrastructure.hpp>
#include <Graphics/Text.hpp>

int main(int _argc, char **_argv) {

	try {
#if 1
		Driller::initialiseManagers();
		Driller::start();
#endif
#if 0
		Pong::initialiseManagers();
		Pong::start();
#endif
	}
	catch (std::exception const& _ex) {
		std::cout << "Exception: " << _ex.what() << std::endl;
		getchar();
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}