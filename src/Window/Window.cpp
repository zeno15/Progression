#include <Window/Window.hpp>

#include <Window/OpenGL.hpp>

#include <Graphics/Colour.hpp>

#include <SDL.h>

#include <iostream>

namespace Window {

	bool Window::m_SDLInitialised = false;

	Window::Window(void) :
		m_VideoMode(),
		m_Title(std::string()),
		m_WindowStyle(WindowStyle::Default) {
	}

	Window::Window(const VideoMode& _videoMode, const std::string& _title, uint32_t _style /*= WindowStyle::Default*/) :
		m_VideoMode(_videoMode),
		m_Title(_title),
		m_WindowStyle(_style) {
		create(m_VideoMode, m_Title, m_WindowStyle);
	}

	Window::~Window(void) {
		close();
	}


	bool Window::create(const VideoMode& _videoMode, const std::string& _title, uint32_t _style /*= WindowStyle::Default*/) {
		if (!m_SDLInitialised) {
			m_SDLInitialised = true;
			int result = SDL_Init(SDL_INIT_EVERYTHING);
			if (result < 0) {
				return false;
			}
		}

		m_Window = SDL_CreateWindow(
			_title.c_str(), 
			SDL_WINDOWPOS_CENTERED, 
			SDL_WINDOWPOS_CENTERED, 
			static_cast<int>(_videoMode.width), 
			static_cast<int>(_videoMode.height), 
			SDL_WINDOW_OPENGL);

		if (!m_Window) {
			return false;
		}

		m_VideoMode = _videoMode;
		m_Title = _title;
		m_WindowStyle = _style;
		
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, _videoMode.major);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, _videoMode.minor);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		m_OpenGLContext = SDL_GL_CreateContext(m_Window);

		if (!m_OpenGLContext) {
			return false;
		}


		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		return true;
	}

	void Window::close(void) {
	}

	bool Window::isOpen(void) const {
		throw std::runtime_error("Window::isOpen");
	}

	System::Vector2i Window::getPosition(void) const {
		throw std::runtime_error("Window::getPosition");
	}

	void Window::setPosition(const System::Vector2i& _position) {
	}

	System::Vector2u Window::getSize(void) const {
		throw std::runtime_error("Window::getSize");
	}

	void Window::setSize(const System::Vector2u& _size) {
	}

	void Window::display(void) {
		SDL_GL_SwapWindow(m_Window);
	}

	void Window::clear(void) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	bool Window::pollEvent(System::Event& _event) {
		SDL_Event sdlEvent;
		bool hasEvent = SDL_PollEvent(&sdlEvent);
		if (hasEvent) {
			mapSDLToCustomEvent(sdlEvent, _event);
		}
		return hasEvent;
	}
	void Window::waitEvent(System::Event& _event) {
	}

	void Window::setRepeatedKeys(bool _repeat) {
	}

	void Window::setTitle(const std::string& _title) {
	}

	std::string Window::getTitle(void) const {
		throw std::runtime_error("Window::getTitle");
	}

	void Window::mapSDLToCustomEvent(SDL_Event& _sdlEvent, System::Event& _customEvent) {
		switch (_sdlEvent.type) {
		case SDL_QUIT:
			_customEvent.type = System::Event::EventType::WindowClosed;
			break;
		}
	}
}