#include <Driller/Managers/UserInteractionManager.hpp>

#include <Driller/Managers/NotificationService.hpp>

#include <Driller/DrillerDefinitions.hpp>
#include <Driller/DrillerResources.hpp>

#include <Infrastructure/Application.hpp>
#include <Infrastructure/Camera.hpp>
#include <Infrastructure/InstanceCollection.hpp>
#include <Infrastructure/ShaderManager.hpp>

#include <System/Event.hpp>

#include <iostream>

namespace Driller {
	const std::string UserInteractionManager::Name = "UserInteractionManager";

	UserInteractionManager::UserInteractionManager(void) :
		m_CurrentTileInteractionContext(DrillerDefinitions::TileInteractionContext::NoContext) {

	}


	bool UserInteractionManager::handleEvent(const System::Event& _event) {
		if (checkForActivatedTile(_event)) {
			return true;
		}

		return false;
	}

	System::Vector2i UserInteractionManager::getTilePositionFromWorldCoordinates(const System::Vector2f& _worldCoordinates) {
		auto floatTilesY = _worldCoordinates.y / DrillerDefinitions::TileHeight;

		if (std::fabsf(_worldCoordinates.x) < DrillerDefinitions::TileWidth / 2.0f) {
			return System::Vector2i(0, static_cast<int>(-floatTilesY));
		}

		if (_worldCoordinates.x > 0) {
			return System::Vector2i(
				static_cast<int>((_worldCoordinates.x - DrillerDefinitions::TileWidth / 2.0f) / DrillerDefinitions::TileWidth) + 1,
				static_cast<int>(-floatTilesY));
		}
		else {
			return System::Vector2i(
				static_cast<int>((_worldCoordinates.x + DrillerDefinitions::TileWidth / 2.0f) / DrillerDefinitions::TileWidth) - 1,
				static_cast<int>(-floatTilesY));
		}
	}

	bool UserInteractionManager::checkForActivatedTile(const System::Event& _event) {
		if (_event.type == System::Event::MouseButtonPressed) {
			auto size = System::Vector2f(Infrastructure::InstanceCollection::getInstance<Infrastructure::Application>().getWindow().getSize());
			auto cameraPosition = Infrastructure::InstanceCollection::getInstance<Infrastructure::Camera>().getPosition();

			float x = cameraPosition.x + static_cast<float>(_event.mouseButton.x) - size.x / 2.0f;
			float y = cameraPosition.y + size.y - static_cast<float>(_event.mouseButton.y) - size.y / 2.0f;

			if (y > 0) {
				return false;
			}

			auto tileCoordinates = getTilePositionFromWorldCoordinates(System::Vector2f(x, y));

			if (std::abs(tileCoordinates.x) > DrillerDefinitions::MaximumWidth) {
				return false;
			}

			if (m_CurrentTileInteractionContext == DrillerDefinitions::TileInteractionContext::NoContext) {
				Infrastructure::InstanceCollection::getInstance<NotificationService>().OnTileActivated.invoke(tileCoordinates.x, tileCoordinates.y, m_CurrentTileInteractionContext);

				return true;
			}
		}

		return false;
	}
	System::Vector2i UserInteractionManager::getTilePositionFromEventCoordinates(const System::Vector2i& _eventCoordinates) {
		auto size = System::Vector2f(Infrastructure::InstanceCollection::getInstance<Infrastructure::Application>().getWindow().getSize());
		auto cameraPosition = Infrastructure::InstanceCollection::getInstance<Infrastructure::Camera>().getPosition();

		float x = cameraPosition.x + static_cast<float>(_eventCoordinates.x) - size.x / 2.0f;
		float y = cameraPosition.y + size.y - static_cast<float>(_eventCoordinates.y) - size.y / 2.0f;

		return getTilePositionFromWorldCoordinates(System::Vector2f(x, y));
	}
	System::Vector2f UserInteractionManager::getWorldPositionFromEventCoordinates(const System::Vector2i& _eventCoordinates) {
		auto size = System::Vector2f(Infrastructure::InstanceCollection::getInstance<Infrastructure::Application>().getWindow().getSize());
		auto cameraPosition = Infrastructure::InstanceCollection::getInstance<Infrastructure::Camera>().getPosition();

		float x = cameraPosition.x + static_cast<float>(_eventCoordinates.x) - size.x / 2.0f;
		float y = cameraPosition.y + size.y - static_cast<float>(_eventCoordinates.y) - size.y / 2.0f;

		return System::Vector2f(x, y);
	}

	void UserInteractionManager::updateCurrentTileInteractionContext(DrillerDefinitions::TileInteractionContext _context) {
		m_CurrentTileInteractionContext = _context;
	}
	DrillerDefinitions::TileInteractionContext UserInteractionManager::getCurrentTileInteractionContext(void) const {
		return m_CurrentTileInteractionContext;
	}
}