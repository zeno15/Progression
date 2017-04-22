#include <Tower/Scenes/TowerGameScene.hpp>

#include <Tower/Managers/CreepManager.hpp>
#include <Tower/Managers/LevelManager.hpp>
#include <Tower/Managers/LevelInteractionManager.hpp>
#include <Tower/Managers/ProjectileManager.hpp>
#include <Tower/Managers/TowerManager.hpp>
#include <Tower/Managers/UserInteractionManager.hpp>

#include <Infrastructure/InstanceCollection.hpp>
#include <Infrastructure/Application.hpp>
#include <Infrastructure/Camera.hpp>

#include <iostream>

namespace Tower {

	TowerGameScene::TowerGameScene(void) :
		Infrastructure::Scene("TowerGameScene") {

	}

	TowerGameScene::~TowerGameScene(void) {

	}


	void TowerGameScene::update(float _delta) {
		Infrastructure::InstanceCollection::getInstance<LevelManager>().update(_delta);
		Infrastructure::InstanceCollection::getInstance<ProjectileManager>().update(_delta);
		Infrastructure::InstanceCollection::getInstance<CreepManager>().update(_delta);
		Infrastructure::InstanceCollection::getInstance<TowerManager>().update(_delta);
		Infrastructure::InstanceCollection::getInstance<LevelInteractionManager>().update(_delta);
		Infrastructure::InstanceCollection::getInstance<UserInteractionManager>().update(_delta);
	}

	bool TowerGameScene::handleEvent(const System::Event& _event) {
		if (Infrastructure::InstanceCollection::getInstance<UserInteractionManager>().handleEvent(_event)) {
			return true;
		}
		if (Infrastructure::InstanceCollection::getInstance<LevelInteractionManager>().handleEvent(_event)) {
			return true;
		}
		if (Infrastructure::InstanceCollection::getInstance<LevelManager>().handleEvent(_event)) {
			return true;
		}
		if (Infrastructure::InstanceCollection::getInstance<CreepManager>().handleEvent(_event)) {
			return true;
		}
		if (Infrastructure::InstanceCollection::getInstance<TowerManager>().handleEvent(_event)) {
			return true;
		}
		if (Infrastructure::InstanceCollection::getInstance<ProjectileManager>().handleEvent(_event)) {
			return true;
		}
		if (_event.type == System::Event::KeyDown) {
			if (_event.key.key == System::Keyboard::F1) {
				Infrastructure::InstanceCollection::getInstance<LevelManager>().loadLevel("Level1");
				return true;
			}
			if (_event.key.key == System::Keyboard::F2) {
				Infrastructure::InstanceCollection::getInstance<CreepManager>().addCreep(new Creep(4.0f), &Infrastructure::InstanceCollection::getInstance<LevelManager>().getLevel().getTile(0, 0));
				return true;
			}
		}
		if (_event.type == System::Event::MouseButtonPressed) {
			if (Infrastructure::InstanceCollection::getInstance<LevelInteractionManager>().isMousePositionWithinLevelBounds(System::Vector2f(_event.mouseButton.x, _event.mouseButton.y))) {
				auto pos = Infrastructure::InstanceCollection::getInstance<LevelInteractionManager>().getTileCoordinatesFromMousePosition(System::Vector2f(_event.mouseButton.x, _event.mouseButton.y));

				std::cout << "Tile position " << pos << std::endl;
			}
		}
		return false;
	}

	void TowerGameScene::render(const Window::Window& _window, Graphics::RenderData) const {
		auto size = System::Vector2f(Infrastructure::InstanceCollection::getInstance<Infrastructure::Application>().getWindow().getSize());
		auto cameraPosition = Infrastructure::InstanceCollection::getInstance<Infrastructure::Camera>().getPosition();
		auto zoom = Infrastructure::InstanceCollection::getInstance<Infrastructure::Camera>().getZoom();

		System::Mat4x4 view = System::Mat4x4::createTranslation(System::Vector3f(-cameraPosition.x, -cameraPosition.y, 0.0f));
		System::Mat4x4 projection = System::Mat4x4::Orthographic2D(
			-(size.x / 2.0f) / zoom,
			+(size.x / 2.0f) / zoom,
			+(size.y / 2.0f) / zoom,
			-(size.y / 2.0f) / zoom);

		Graphics::RenderData renderData = Graphics::RenderData(view, projection);

		Infrastructure::InstanceCollection::getInstance<LevelManager>().render(_window, renderData);
		Infrastructure::InstanceCollection::getInstance<CreepManager>().render(_window, renderData);
		Infrastructure::InstanceCollection::getInstance<TowerManager>().render(_window, renderData);
		Infrastructure::InstanceCollection::getInstance<ProjectileManager>().render(_window, renderData);
		Infrastructure::InstanceCollection::getInstance<LevelInteractionManager>().render(_window, renderData);
		Infrastructure::InstanceCollection::getInstance<UserInteractionManager>().render(_window, renderData);
	}
}