#include <Driller/Managers/ShuttleManager.hpp>

#include <Driller/DrillerDefinitions.hpp>

namespace Driller {
	const std::string ShuttleManager::Name = "ShuttleManager";
	
	ShuttleManager::ShuttleManager(void) :
		m_TimeToShuttleArrival(0.0f),
		m_IsShuttleInTransit(false) {

	}

	
	void ShuttleManager::update(float _delta) {
		if (m_IsShuttleInTransit) {
			m_Shuttle->update(_delta);
			if (m_Shuttle->hasFinishedDeparture()) {
				m_IsShuttleInTransit = false;
				m_TimeToShuttleArrival = DrillerDefinitions::ShuttleInterval;
			}
		}
		else {
			m_TimeToShuttleArrival -= _delta;
			if (m_TimeToShuttleArrival <= 0.0f) {
				m_IsShuttleInTransit = true;
				m_Shuttle->resetForArrival();
			}
		}
	}

	void ShuttleManager::render(const Window::Window& _window, Graphics::RenderData _renderData) const {
		if (m_IsShuttleInTransit) {
			m_Shuttle->render(_window, _renderData);
		}
	}

	void ShuttleManager::createShuttle(void) {
		m_Shuttle = new ShuttleElement();
	}
}