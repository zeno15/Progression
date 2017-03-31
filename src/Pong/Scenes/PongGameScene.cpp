#include <Pong/Scenes/PongGameScene.hpp>

#include <Pong/Managers/GameObjectManager.hpp>

#include <Pong/GameObjects/Ball.hpp>
#include <Pong/GameObjects/Board.hpp>
#include <Pong/GameObjects/Paddle.hpp>

#include <Pong/PongResources.hpp>

#include <Infrastructure/InstanceCollection.hpp>
#include <Infrastructure/Application.hpp>
#include <Infrastructure/Camera.hpp>
#include <Infrastructure/FontManager.hpp>

#include <iostream>

namespace Pong {

	PongGameScene::PongGameScene(void) :
		Scene("PongGameScene"),
		m_LeftPlayerScore(0),
		m_RightPlayerScore(0) {
		Infrastructure::InstanceCollection::getInstance<GameObjectManager>().addGameObject(new Ball());
		Infrastructure::InstanceCollection::getInstance<GameObjectManager>().addGameObject(new Board());
		Infrastructure::InstanceCollection::getInstance<GameObjectManager>().addGameObject(new Paddle("LeftPaddle", Graphics::Colour::Magenta, PongDefinitions::PaddleTeam::Left));
		Infrastructure::InstanceCollection::getInstance<GameObjectManager>().addGameObject(new Paddle("RightPaddle", Graphics::Colour::Cyan, PongDefinitions::PaddleTeam::Right));

		m_LeftPlayerScoreText.setColour(Graphics::Colour::Red);
		m_RightPlayerScoreText.setColour(Graphics::Colour::Red);
		m_LeftPlayerScoreText.setPosition(System::Vector2f(220.0f, 600.0f));
		m_RightPlayerScoreText.setPosition(System::Vector2f(1020.0f, 600.0f));
		m_LeftPlayerScoreText.generateText(std::to_string(m_LeftPlayerScore), &Infrastructure::InstanceCollection::getInstance<Infrastructure::FontManager>().getFont(PongResources::DefaultFontName));
		m_RightPlayerScoreText.generateText(std::to_string(m_RightPlayerScore), &Infrastructure::InstanceCollection::getInstance<Infrastructure::FontManager>().getFont(PongResources::DefaultFontName));

		Infrastructure::InstanceCollection::getInstance<Infrastructure::FontManager>().getFont(PongResources::DefaultFontName).getAtlas().saveToFile("C:/Users/markd/Desktop/Test.png");
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

		System::Mat4x4 view = System::Mat4x4::createTranslation(System::Vector3f(-cameraPosition.x, -cameraPosition.y - 50.0f, 0.0f));
		System::Mat4x4 projection = System::Mat4x4::Orthographic2D(
			-(size.x / 2.0f) / zoom,
			+(size.x / 2.0f) / zoom,
			+(size.y / 2.0f) / zoom,
			-(size.y / 2.0f) / zoom);

		Graphics::RenderData renderData = Graphics::RenderData(view, projection);
		Infrastructure::InstanceCollection::getInstance<GameObjectManager>().render(_window, renderData);


		renderData.view = System::Mat4x4(1.0f);
		renderData.projection = System::Mat4x4::Orthographic2D(0.0f, size.x, size.y, 0.0f);
		m_LeftPlayerScoreText.render(_window, renderData);
		m_RightPlayerScoreText.render(_window, renderData);
	}

	void PongGameScene::ballLost(const PongDefinitions::PaddleTeam& _losingTeam, Ball *_ball) {
		std::cout << "PongGameScene::ballLost: " << _losingTeam << std::endl;
		Infrastructure::InstanceCollection::getInstance<GameObjectManager>().removeGameObject(_ball);
		Infrastructure::InstanceCollection::getInstance<GameObjectManager>().addGameObject(new Ball());

		if (_losingTeam == PongDefinitions::PaddleTeam::Left) {
			m_RightPlayerScore += 1;
		}
		else {
			m_LeftPlayerScore += 1;
		}

		m_LeftPlayerScoreText.generateText(std::to_string(m_LeftPlayerScore), &Infrastructure::InstanceCollection::getInstance<Infrastructure::FontManager>().getFont(PongResources::DefaultFontName));
		m_RightPlayerScoreText.generateText(std::to_string(m_RightPlayerScore), &Infrastructure::InstanceCollection::getInstance<Infrastructure::FontManager>().getFont(PongResources::DefaultFontName));
	}
}