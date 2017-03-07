/*
 * Copyright (c) <year> <author> (<email>)
 * Distributed under the MIT License.
 * See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT
 */

#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <SFML/Graphics.hpp>


int main( const int _argc, const char **_argv ) {
	sf::Vector2f vec;
	vec.x = 5.2f;
	vec.y = 21.2f;
	std::cout << "Hello World! x: " << vec.x << ", y: " << vec.y << std::endl;

	return EXIT_SUCCESS;
}
