#include <Infrastructure/Application.hpp>

#include <Infrastructure/InstanceCollection.hpp>
#include <Infrastructure/SceneManager.hpp>
#include <Infrastructure/ShaderManager.hpp>

#include <System/Clock.hpp>
#include <Window/OpenGL.hpp>

#include <iostream>

namespace Infrastructure {

	const std::string Application::Name = "Application";

	Application::Application() : m_Running(false) {}

	Application::~Application() {}


	void Application::initialise(const System::Vector2u& _size, const std::string& _title) {
		Window::VideoMode videoMode = Window::VideoMode();
		videoMode.bitsPerPixel = 32;
		videoMode.width = _size.x;
		videoMode.height = _size.y;
		videoMode.major = 4;
		videoMode.minor = 5;
		m_Window.create(videoMode, _title, Window::WindowStyle::Titlebar | Window::WindowStyle::Close);
		//m_Window.setVerticalSyncEnabled(true);

		InstanceCollection::getInstance<ShaderManager>().initialiseSystemShaders();

		std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
		std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
		std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
		std::cout << "Shading langauge version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
	}

	void Application::start(void) {
		m_Running = true;

		float dt = 1.0f / 60.0f;
		float accumulator = 0.0f;
		float statsAccumulator = 0.0f;

		unsigned int fps = 0;
		unsigned int ups = 0;
		unsigned int fpsAccumulator = 0;
		unsigned int upsAccumulator = 0;

		System::Clock clock;



		while (m_Running) {

			float frameTime = clock.restart().asSeconds();
			if (frameTime > 0.25f) {
				frameTime = 0.25f;
				std::cerr << "FrameTime > 0.25 seconds" << std::endl;
			}

			accumulator += frameTime;
			statsAccumulator += frameTime;
			if (statsAccumulator >= 1.0f) {
				statsAccumulator -= 1.0f;
				fps = fpsAccumulator;
				ups = upsAccumulator;
				fpsAccumulator = 0;
				upsAccumulator = 0;
				std::cout << "FPS: " << fps << ", UPS: " << ups << std::endl;
			}

			while (accumulator >= dt) {
				update(dt);
				accumulator -= dt;
				upsAccumulator += 1;
			}

			render(accumulator / dt);
			fpsAccumulator += 1;
		}

		m_Window.close();
	}

	void Application::update(float _delta) {


		System::Event event;
		while (m_Window.pollEvent(event)) {

			if (event.type == System::Event::WindowClosed) {
				m_Running = false;
			}
			if (event.type == System::Event::WindowSizeChanged) {
				glViewport(0, 0, event.size.width, event.size.height);
			}

			Infrastructure::InstanceCollection::getInstance<Infrastructure::SceneManager>().handleEvent(event);
		}

		Infrastructure::InstanceCollection::getInstance<Infrastructure::SceneManager>().update(_delta);

	}
	void Application::render(float _alpha) {
		m_Window.clear();

		Infrastructure::InstanceCollection::getInstance<Infrastructure::SceneManager>().draw(m_Window, Graphics::RenderData());

		m_Window.display();
	}

	void Application::stop(void) {
		m_Running = false;
	}

	Window::Window& Application::getWindow(void) {
		return m_Window;
	}

	bool Application::isRunning(void) const {
		return m_Running;
	}
}