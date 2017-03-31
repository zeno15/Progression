#include <Pong/GameObjects/Paddle.hpp>

#include <Pong/GameObjects/Ball.hpp>

#include <Pong/Managers/GameObjectManager.hpp>

#include <Pong/PongDefinitions.hpp>
#include <Pong/PongResources.hpp>

#include <Infrastructure.hpp>

#include <System/Rect.hpp>

#include <Window/OpenGL.hpp>

#include <iostream>
#include <cassert>

namespace Pong {

	Paddle::Paddle(void) :
		Paddle("Paddle", Graphics::Colour::Magenta, PongDefinitions::PaddleTeam::Left) {
	}
	Paddle::Paddle(const std::string& _name, const Graphics::Colour& _colour, PongDefinitions::PaddleTeam _team) :
		GameObject(_name),
		m_VAO(0),
		m_VBO(0),
		m_Offset(0.0f),
		m_Colour(_colour),
		m_Team(_team) {

		std::vector<float> data = {
			-PongDefinitions::PaddleWidth / 2.0f, -PongDefinitions::PaddleHeight / 2.0f,
			+PongDefinitions::PaddleWidth / 2.0f, -PongDefinitions::PaddleHeight / 2.0f,
			+PongDefinitions::PaddleWidth / 2.0f, +PongDefinitions::PaddleHeight / 2.0f,

			-PongDefinitions::PaddleWidth / 2.0f, -PongDefinitions::PaddleHeight / 2.0f,
			+PongDefinitions::PaddleWidth / 2.0f, +PongDefinitions::PaddleHeight / 2.0f,
			-PongDefinitions::PaddleWidth / 2.0f, +PongDefinitions::PaddleHeight / 2.0f,
		};

		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);

		glGenBuffers(1, &m_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * data.size(), data.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void *)(0 * sizeof(float)));
	}


	void Paddle::update(float _delta) {
		float offset = 0.0f;
		if (System::Keyboard::isKeyDown(PongDefinitions::KeyBindings[m_Team][PongDefinitions::KeyBindings::MoveUp])) {
			// Up
			offset += 1.0f;
		}
		if (System::Keyboard::isKeyDown(PongDefinitions::KeyBindings[m_Team][PongDefinitions::KeyBindings::MoveDown])) {
			// Down
			offset -= 1.0f;
		}

		m_Offset += offset * PongDefinitions::PaddleBaseSpeed * _delta;

		clampPaddleToBounds();

		auto&gom = Infrastructure::InstanceCollection::getInstance<GameObjectManager>();

		// TODO: if multiple balls are present this needs to go through all not just one.
		auto ball = dynamic_cast<Ball *>(gom.getGameObject("Ball"));

		if (ball != nullptr) {
			auto ballPosition = ball->getPosition();
			auto ballVelocity = ball->getVelocity();

			auto ballDistanceFromCenter = std::fabsf(std::fabsf(ballPosition.x) - PongDefinitions::BoardWidth / 2.0f);

			if (ballDistanceFromCenter < (PongDefinitions::BallSize + PongDefinitions::PaddleWidth) / 2.0f) {

				float ballMaxY = ballPosition.y + PongDefinitions::BallSize / 2.0f;
				float ballMinY = ballPosition.y - PongDefinitions::BallSize / 2.0f;

				float paddleMaxY = m_Offset + PongDefinitions::PaddleHeight / 2.0f;
				float paddleMinY = m_Offset - PongDefinitions::PaddleHeight / 2.0f;

				if (paddleMinY < ballMaxY && ballMaxY < paddleMaxY ||
					paddleMinY < ballMinY && ballMinY < paddleMaxY) {
					ball->setVelocity(System::Vector2f(-ballVelocity.x, ballVelocity.y));
				}
			}
		}
	}

	void Paddle::render(const Window::Window& _window, Graphics::RenderData _renderData) const {

		auto& shader = Infrastructure::InstanceCollection::getInstance<Infrastructure::ShaderManager>().getShader(PongResources::SolidNoTextureShaderName);
		shader.bind();
		shader.passUniform(PongResources::SolidNoTextureShaderUniformColour, m_Colour);
		shader.passUniform(PongResources::SolidNoTextureShaderUniformMVP,
			_renderData.projection *
			_renderData.view *
			System::Mat4x4::createTranslation(System::Vector3f(
				(PongDefinitions::BoardWidth / 2.0f - PongDefinitions::PaddleWidth / 2.0f) * (m_Team == PongDefinitions::PaddleTeam::Left ? -1.0f : 1.0f),
				m_Offset,
				0.0f)));

		glBindVertexArray(m_VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
	
	void Paddle::clampPaddleToBounds(void) {
		const float maximum = +PongDefinitions::BoardHeight / 2.0f - PongDefinitions::PaddleHeight / 2.0f;
		const float minimum = -PongDefinitions::BoardHeight / 2.0f + PongDefinitions::PaddleHeight / 2.0f;

		if (m_Offset > maximum) {
			m_Offset = maximum;
		}
		if (m_Offset < minimum) {
			m_Offset = minimum;
		}
	}
}