#include <Pong/Scenes/PongGameScene.hpp>

#include <Pong/Managers/GameObjectManager.hpp>

#include <Pong/GameObjects/Ball.hpp>
#include <Pong/GameObjects/Board.hpp>
#include <Pong/GameObjects/Paddle.hpp>

#include <Infrastructure/InstanceCollection.hpp>
#include <Infrastructure/Application.hpp>
#include <Infrastructure/Camera.hpp>

#include <iostream>

namespace Pong {

	PongGameScene::PongGameScene(void) :
		Scene("PongGameScene") {
		Infrastructure::InstanceCollection::getInstance<GameObjectManager>().addGameObject(new Ball());
		Infrastructure::InstanceCollection::getInstance<GameObjectManager>().addGameObject(new Board());
		Infrastructure::InstanceCollection::getInstance<GameObjectManager>().addGameObject(new Paddle("LeftPaddle", Graphics::Colour::Magenta, PongDefinitions::PaddleTeam::Left));
		Infrastructure::InstanceCollection::getInstance<GameObjectManager>().addGameObject(new Paddle("RightPaddle", Graphics::Colour::Cyan, PongDefinitions::PaddleTeam::Right));
	}
	PongGameScene::~PongGameScene(void) {

	}

	void PongGameScene::update(float _delta) {
		Infrastructure::InstanceCollection::getInstance<GameObjectManager>().update(_delta);
	}

	bool PongGameScene::handleEvent(const System::Event& _event) {
		return false;
	}

	void PongGameScene::render(const Window::Window& _window, Graphics::RenderData) const {

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
		Infrastructure::InstanceCollection::getInstance<GameObjectManager>().render(_window, renderData);
	}

	void PongGameScene::ballLost(const PongDefinitions::PaddleTeam& _losingTeam, Ball *_ball) {
		std::cout << "PongGameScene::ballLost: " << _losingTeam << std::endl;
		Infrastructure::InstanceCollection::getInstance<GameObjectManager>().removeGameObject(_ball);
	}
}