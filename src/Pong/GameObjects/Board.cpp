#include <Pong/GameObjects/Board.hpp>

#include <Pong/PongDefinitions.hpp>
#include <Pong/PongResources.hpp>

#include <Infrastructure/InstanceCollection.hpp>
#include <Infrastructure/ShaderManager.hpp>

#include <Window/OpenGL.hpp>

namespace Pong {

	Board::Board(void) :
		GameObject("Board"),
		m_VAO(0),
		m_VBO(0) {

		std::vector<float> data = {
			// Bottom side
			-PongDefinitions::BoardWidth / 2.0f + PongDefinitions::BoardOutlineThickness * 0.0f, -PongDefinitions::BoardHeight / 2.0f - PongDefinitions::BoardOutlineThickness * 1.0f,
			+PongDefinitions::BoardWidth / 2.0f + PongDefinitions::BoardOutlineThickness * 1.0f, -PongDefinitions::BoardHeight / 2.0f - PongDefinitions::BoardOutlineThickness * 1.0f,
			+PongDefinitions::BoardWidth / 2.0f + PongDefinitions::BoardOutlineThickness * 1.0f, -PongDefinitions::BoardHeight / 2.0f + PongDefinitions::BoardOutlineThickness * 0.0f,

			-PongDefinitions::BoardWidth / 2.0f + PongDefinitions::BoardOutlineThickness * 0.0f, -PongDefinitions::BoardHeight / 2.0f - PongDefinitions::BoardOutlineThickness * 1.0f,
			+PongDefinitions::BoardWidth / 2.0f + PongDefinitions::BoardOutlineThickness * 1.0f, -PongDefinitions::BoardHeight / 2.0f + PongDefinitions::BoardOutlineThickness * 0.0f,
			-PongDefinitions::BoardWidth / 2.0f + PongDefinitions::BoardOutlineThickness * 0.0f, -PongDefinitions::BoardHeight / 2.0f + PongDefinitions::BoardOutlineThickness * 0.0f,

			// Right side
			+PongDefinitions::BoardWidth / 2.0f + PongDefinitions::BoardOutlineThickness * 0.0f, -PongDefinitions::BoardHeight / 2.0f + PongDefinitions::BoardOutlineThickness * 0.0f,
			+PongDefinitions::BoardWidth / 2.0f + PongDefinitions::BoardOutlineThickness * 1.0f, -PongDefinitions::BoardHeight / 2.0f + PongDefinitions::BoardOutlineThickness * 0.0f,
			+PongDefinitions::BoardWidth / 2.0f + PongDefinitions::BoardOutlineThickness * 1.0f, +PongDefinitions::BoardHeight / 2.0f + PongDefinitions::BoardOutlineThickness * 1.0f,

			+PongDefinitions::BoardWidth / 2.0f + PongDefinitions::BoardOutlineThickness * 0.0f, -PongDefinitions::BoardHeight / 2.0f + PongDefinitions::BoardOutlineThickness * 0.0f,
			+PongDefinitions::BoardWidth / 2.0f + PongDefinitions::BoardOutlineThickness * 1.0f, +PongDefinitions::BoardHeight / 2.0f + PongDefinitions::BoardOutlineThickness * 1.0f,
			+PongDefinitions::BoardWidth / 2.0f + PongDefinitions::BoardOutlineThickness * 0.0f, +PongDefinitions::BoardHeight / 2.0f + PongDefinitions::BoardOutlineThickness * 1.0f,

			// Top side
			-PongDefinitions::BoardWidth / 2.0f - PongDefinitions::BoardOutlineThickness * 1.0f, +PongDefinitions::BoardHeight / 2.0f + PongDefinitions::BoardOutlineThickness * 0.0f,
			+PongDefinitions::BoardWidth / 2.0f + PongDefinitions::BoardOutlineThickness * 0.0f, +PongDefinitions::BoardHeight / 2.0f + PongDefinitions::BoardOutlineThickness * 0.0f,
			+PongDefinitions::BoardWidth / 2.0f + PongDefinitions::BoardOutlineThickness * 0.0f, +PongDefinitions::BoardHeight / 2.0f + PongDefinitions::BoardOutlineThickness * 1.0f,

			-PongDefinitions::BoardWidth / 2.0f - PongDefinitions::BoardOutlineThickness * 1.0f, +PongDefinitions::BoardHeight / 2.0f + PongDefinitions::BoardOutlineThickness * 0.0f,
			+PongDefinitions::BoardWidth / 2.0f + PongDefinitions::BoardOutlineThickness * 0.0f, +PongDefinitions::BoardHeight / 2.0f + PongDefinitions::BoardOutlineThickness * 1.0f,
			-PongDefinitions::BoardWidth / 2.0f - PongDefinitions::BoardOutlineThickness * 1.0f, +PongDefinitions::BoardHeight / 2.0f + PongDefinitions::BoardOutlineThickness * 1.0f,

			// Left side
			-PongDefinitions::BoardWidth / 2.0f - PongDefinitions::BoardOutlineThickness * 1.0f, -PongDefinitions::BoardHeight / 2.0f - PongDefinitions::BoardOutlineThickness * 1.0f,
			-PongDefinitions::BoardWidth / 2.0f + PongDefinitions::BoardOutlineThickness * 0.0f, -PongDefinitions::BoardHeight / 2.0f - PongDefinitions::BoardOutlineThickness * 1.0f,
			-PongDefinitions::BoardWidth / 2.0f + PongDefinitions::BoardOutlineThickness * 0.0f, +PongDefinitions::BoardHeight / 2.0f + PongDefinitions::BoardOutlineThickness * 0.0f,

			-PongDefinitions::BoardWidth / 2.0f - PongDefinitions::BoardOutlineThickness * 1.0f, -PongDefinitions::BoardHeight / 2.0f - PongDefinitions::BoardOutlineThickness * 1.0f,
			-PongDefinitions::BoardWidth / 2.0f + PongDefinitions::BoardOutlineThickness * 0.0f, +PongDefinitions::BoardHeight / 2.0f + PongDefinitions::BoardOutlineThickness * 0.0f,
			-PongDefinitions::BoardWidth / 2.0f - PongDefinitions::BoardOutlineThickness * 1.0f, +PongDefinitions::BoardHeight / 2.0f + PongDefinitions::BoardOutlineThickness * 0.0f,
		};

		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);

		glGenBuffers(1, &m_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * data.size(), data.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void *)(0 * sizeof(float)));
	}

	void Board::update(float _delta) {

	}

	void Board::render(const Window::Window& _window, Graphics::RenderData _renderData) const {

		auto& shader = Infrastructure::InstanceCollection::getInstance<Infrastructure::ShaderManager>().getShader(PongResources::SolidNoTextureShaderName);
		shader.bind();
		shader.passUniform(PongResources::SolidNoTextureShaderUniformColour, Graphics::Colour::Black);
		shader.passUniform(PongResources::SolidNoTextureShaderUniformMVP,
			_renderData.projection *
			_renderData.view *
			System::Mat4x4::createTranslation(System::Vector3f(
				0.0f,
				0.0f,
				-0.1f)));

		glBindVertexArray(m_VAO);
		glDrawArrays(GL_TRIANGLES, 0, 24);
	}
}