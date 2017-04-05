#include <cstdlib>
#include <iostream>

#include <Driller/DrillerStart.hpp>
#include <Pong/PongStart.hpp>

#include <Window/Window.hpp>
#include <Window/OpenGL.hpp>
#include <Infrastructure.hpp>
#include <Graphics/Text.hpp>

#define DRILLER 1
#define PONG 0

int main(int _argc, char **_argv) {

	try {
#if DRILLER
		Driller::initialiseManagers();
		Driller::start();
#endif
#if PONG
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