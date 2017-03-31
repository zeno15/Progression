#include <Pong/GameObjects/Ball.hpp>

#include <Pong/PongDefinitions.hpp>
#include <Pong/PongResources.hpp>

#include <Pong/Managers/NotificationManager.hpp>

#include <Infrastructure/InstanceCollection.hpp>
#include <Infrastructure/ShaderManager.hpp>

#include <Window/OpenGL.hpp>

#include <iostream>

namespace Pong {
	Ball::Ball(void) :
		GameObject("Ball"),
		m_VAO(0),
		m_VBO(0) {

		std::vector<float> data = {
			-PongDefinitions::BallSize / 2.0f, -PongDefinitions::BallSize / 2.0f,
			+PongDefinitions::BallSize / 2.0f, -PongDefinitions::BallSize / 2.0f,
			+PongDefinitions::BallSize / 2.0f, +PongDefinitions::BallSize / 2.0f,

			-PongDefinitions::BallSize / 2.0f, -PongDefinitions::BallSize / 2.0f,
			+PongDefinitions::BallSize / 2.0f, +PongDefinitions::BallSize / 2.0f,
			-PongDefinitions::BallSize / 2.0f, +PongDefinitions::BallSize / 2.0f,
		};

		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);

		glGenBuffers(1, &m_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * data.size(), data.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void *)(0 * sizeof(float)));

		const float minimumAngle = 22.5f;
		const float angleVariation = 45.0f;

		float angle;
		if (rand() % 2 == 0) {
			angle = minimumAngle;
			angle += (rand() % (static_cast<unsigned int>(angleVariation)));
		}
		else {
			angle = 180.0f - minimumAngle;
			angle -= (rand() % (static_cast<unsigned int>(angleVariation)));
		}

		float radians = PongDefinitions::toRadians(angle);

		float x = std::cosf(radians);
		float y = std::sinf(radians);

		m_Velocity = System::Vector2f(x, y) * PongDefinitions::BallInitialSpeed;
	}

	void Ball::update(float _delta) {
		m_Position.y += m_Velocity.y * _delta;

		if (std::fabsf(m_Position.y) - PongDefinitions::BallSize > PongDefinitions::BoardHeight / 2.0f) {
			m_Velocity.y *= -1.0f;
			float over = std::fabsf(PongDefinitions::BoardHeight / 2.0f - (std::fabsf(m_Position.y) - PongDefinitions::BallSize));

			m_Position.y = (std::signbit(m_Velocity.y) ? 1.0f : -1.0f) * (PongDefinitions::BoardHeight / 2.0f - over);
		}

		if (m_Velocity.x * _delta > PongDefinitions::PaddleWidth / 2.0f + PongDefinitions::BallSize / 2.0f) {
			std::cout << "Ball moving faster than size of paddle, could ~ghost~ through" << std::endl;
		}
		m_Position.x += m_Velocity.x * _delta;

		if (std::fabsf(m_Position.x) - PongDefinitions::BallSize > PongDefinitions::BoardWidth / 2.0f) {
			float over = std::fabsf(PongDefinitions::BoardWidth / 2.0f - (std::fabsf(m_Position.x) - PongDefinitions::BallSize));

			if (over > PongDefinitions::BallSize) {
				Infrastructure::InstanceCollection::getInstance<NotificationManager>().onBallLost.invoke(m_Position.x < 0.0f ? PongDefinitions::PaddleTeam::Left : PongDefinitions::PaddleTeam::Right, this);
			}
			if (m_Velocity.x > 0.0f) {
				m_Velocity.x *= -1.0f;
				float over = std::fabsf(PongDefinitions::BoardWidth / 2.0f - (std::fabsf(m_Position.x) - PongDefinitions::BallSize));

				if (over > PongDefinitions::BallSize) {
					std::cout << "Lost" << std::endl;
				}

				m_Position.x = (std::signbit(m_Velocity.x) ? 1.0f : -1.0f) * (PongDefinitions::BoardWidth / 2.0f - over);
			}
		}

	}

	void Ball::render(const Window::Window& _window, Graphics::RenderData _renderData) const {
		auto& shader = Infrastructure::InstanceCollection::getInstance<Infrastructure::ShaderManager>().getShader(PongResources::SolidNoTextureShaderName);
		shader.bind();
		shader.passUniform(PongResources::SolidNoTextureShaderUniformColour, Graphics::Colour::Red);
		shader.passUniform(PongResources::SolidNoTextureShaderUniformMVP,
			_renderData.projection *
			_renderData.view *
			System::Mat4x4::createTranslation(System::Vector3f(
				m_Position,
				0.0f)));

		glBindVertexArray(m_VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	const System::Vector2f& Ball::getPosition(void) const {
		return m_Position;
	}
	void Ball::setPosition(const System::Vector2f& _position) {
		m_Position = _position;
	}

	const System::Vector2f& Ball::getVelocity(void) const {
		return m_Velocity;
	}
	void Ball::setVelocity(const System::Vector2f& _velocity) {
		m_Velocity = _velocity;
	}
}