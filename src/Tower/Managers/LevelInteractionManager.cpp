#include <Tower/Managers/LevelInteractionManager.hpp>
#include <Tower/Managers/LevelManager.hpp>

#include <Tower/TowerDefinitions.hpp>

#include <Infrastructure/Application.hpp>
#include <Infrastructure/InstanceCollection.hpp>
#include <Infrastructure/Camera.hpp>

namespace Tower {
	const std::string LevelInteractionManager::Name = "LevelInteractionManager";

	LevelInteractionManager::LevelInteractionManager(void) {

	}


	void LevelInteractionManager::update(float _delta) {

	}
	bool LevelInteractionManager::handleEvent(const System::Event& _event) {
		return false;
	}
	void LevelInteractionManager::render(const Window::Window& _window, Graphics::RenderData _renderData) const {
	}

	bool LevelInteractionManager::isMousePositionWithinLevelBounds(const System::Vector2f& _mousePosition) {
		auto& levelManager = Infrastructure::InstanceCollection::getInstance<LevelManager>();
		auto tilePosition = getTileCoordinatesFromMousePosition(_mousePosition);

		return
			tilePosition.x >= 0 &&
			tilePosition.y >= 0 &&
			tilePosition.x < levelManager.getLevel().width &&
			tilePosition.y < levelManager.getLevel().width;
	}
	System::Vector2i LevelInteractionManager::getTileCoordinatesFromMousePosition(const System::Vector2f& _mousePosition) {

		auto size = System::Vector2f(Infrastructure::InstanceCollection::getInstance<Infrastructure::Application>().getWindow().getSize());
		auto cameraPosition = Infrastructure::InstanceCollection::getInstance<Infrastructure::Camera>().getPosition();

		float x = cameraPosition.x + static_cast<float>(_mousePosition.x) - size.x / 2.0f;
		float y = cameraPosition.y + size.y - static_cast<float>(_mousePosition.y) - size.y / 2.0f;

		System::Vector2i offset;
		if (x < 0.0f) {
			offset.x -= 1;
		}
		if (y < 0.0f) {
			offset.y -= 1;
		}

		return System::Vector2i(x / TowerDefinitions::TileSize, y / TowerDefinitions::TileSize) + offset;
	}

	System::Vector2i LevelInteractionManager::getCurrentMouseTileCoordinates(void) {
		auto mouse = System::Mouse::getPosition(Infrastructure::InstanceCollection::getInstance<Infrastructure::Application>().getWindow());

		if (isMousePositionWithinLevelBounds(mouse)) {
			return getTileCoordinatesFromMousePosition(mouse);
		}

		return System::Vector2i(-1, -1);
	}
}