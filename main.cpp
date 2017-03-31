#include <cstdlib>
#include <iostream>

#include <Driller/DrillerStart.hpp>
#include <Pong/PongStart.hpp>


int main(int _argc, char **_argv) {

	try {
		//Driller::initialiseManagers();

		//Driller::start();

		Pong::initialiseManagers();

		Pong::start();
	}
	catch (std::exception const& _ex) {
		std::cout << "Exception: " << _ex.what() << std::endl;
		getchar();
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}