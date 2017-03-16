#include <Infrastructure/Application.hpp>

#include <Infrastructure/InstanceCollection.hpp>
#include <Infrastructure/SceneManager.hpp>

#include <iostream>

namespace Infrastructure {

	const std::string Application::Name = "Application";

	Application::Application() : m_Running(false) {}

	Application::~Application() {}


	void Application::initialise(const sf::Vector2u& _size, const std::string& _title) {
		m_Window.create(sf::VideoMode(_size.x, _size.y), _title);
		m_Window.setVerticalSyncEnabled(true);
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

		sf::Clock clock;



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


		sf::Event event;
		while (m_Window.pollEvent(event)) {

			if (event.type == sf::Event::Closed)
				m_Running = false;

			Infrastructure::InstanceCollection::getInstance<Infrastructure::SceneManager>().handleEvent(event);
		}

		Infrastructure::InstanceCollection::getInstance<Infrastructure::SceneManager>().update(_delta);

	}
	void Application::render(float _alpha) {
		m_Window.clear();

		auto states = sf::RenderStates::Default;

		Infrastructure::InstanceCollection::getInstance<Infrastructure::SceneManager>().draw(m_Window, states);

		m_Window.display();
	}

	void Application::stop(void) {
		m_Running = false;
	}

	sf::RenderWindow& Application::getWindow(void) {
		return m_Window;
	}

	bool Application::isRunning(void) const {
		return m_Running;
	}
}