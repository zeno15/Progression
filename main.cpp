#include <cstdlib>
#include <iostream>

#include <SDL.h>

#include <Window/OpenGL.hpp>
#include <Window/Window.hpp>

int main(int _argc, char **_argv) {

	Window::Window window = Window::Window(Window::VideoMode(), "Window Title!", Window::WindowStyle::Default);

	std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "Shading langauge version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;


	bool running = true;
	while (running) {
		System::Event event;
		while (window.pollEvent(event)) {
			if (event.type == System::Event::WindowClosed) {
				running = false;
			}
		}

		window.clear();

		window.display();
	}

	return EXIT_SUCCESS;


	//if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
	//	std::cout << "Failed to init SDL" << std::endl;
	//	getchar();
	//	return EXIT_FAILURE;
	//}

	//auto window = SDL_CreateWindow("Title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL);

	//if (!window) {
	//	std::cout << "Failed to create SDL OpenGL window" << std::endl;
	//	getchar();
	//	return EXIT_FAILURE;
	//}

	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	//SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	//auto context = SDL_GL_CreateContext(window);

	//if (!context) {
	//	std::cout << "Failed to create SDL OpenGL context" << std::endl;
	//	getchar();
	//	return EXIT_FAILURE;
	//}

	//int value = 0;
	//SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &value);
	//std::cout << "SDL_GL_CONTEXT_MAJOR_VERSION : " << value << std::endl;

	//SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &value);
	//std::cout << "SDL_GL_CONTEXT_MINOR_VERSION: " << value << std::endl;

	//glClearColor(0.0, 1.0, 0.5, 1.0);
	//glClear(GL_COLOR_BUFFER_BIT);
	//SDL_GL_SwapWindow(window);

	//bool running = true;

	//while (running) {
	//	SDL_Event event;
	//	while (SDL_PollEvent(&event)) {
	//		if (event.type == SDL_QUIT) {
	//			running = false;
	//			break;
	//		}
	//		if (event.type == SDL_KEYDOWN) {
	//			switch (event.key.keysym.sym) {
	//			case SDLK_ESCAPE:
	//				running = false;
	//				break;
	//			case SDLK_r:
	//				// Cover with red and update
	//				glClearColor(1.0, 0.0, 0.0, 1.0);
	//				glClear(GL_COLOR_BUFFER_BIT);
	//				SDL_GL_SwapWindow(window);
	//				break;
	//			case SDLK_g:
	//				// Cover with green and update
	//				glClearColor(0.0, 1.0, 0.0, 1.0);
	//				glClear(GL_COLOR_BUFFER_BIT);
	//				SDL_GL_SwapWindow(window);
	//				break;
	//			case SDLK_b:
	//				// Cover with blue and update
	//				glClearColor(0.0, 0.0, 1.0, 1.0);
	//				glClear(GL_COLOR_BUFFER_BIT);
	//				SDL_GL_SwapWindow(window);
	//				break;
	//			default:
	//				break;
	//			}
	//		}
	//	}
	//}


	//SDL_GL_DeleteContext(context);

	//SDL_DestroyWindow(window);

	//SDL_Quit();

	//return EXIT_SUCCESS;
}