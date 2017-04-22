#include <Graphics/CircleShape.hpp>

#include <Infrastructure/InstanceCollection.hpp>
#include <Infrastructure/ShaderManager.hpp>

#include <cmath>

namespace Graphics {
	CircleShape::CircleShape(float _radius) :
		CircleShape(_radius, 24) {

	}
	CircleShape::CircleShape(float _radius, unsigned int _segments) :
		m_Radius(_radius),
		m_NumberSegments(_segments) {
		regenerateVerticies();
	}


	void CircleShape::render(const Window::Window& _window, RenderData _renderData) const {
		auto& shader = Infrastructure::InstanceCollection::getInstance<Infrastructure::ShaderManager>().getShader(Infrastructure::ShaderManager::NonTexturedVertexArrayShaderName);
		shader.bind();
		shader.passUniform(Infrastructure::ShaderManager::NonTexturedVertexArrayShaderMVPName,
			_renderData.projection *
			_renderData.view *
			_renderData.model *
			System::Mat4x4::createTranslation(System::Vector3f(
				getPosition(),
				0.0f)));

		m_VertexArray.render(_window, _renderData);
	}

	void CircleShape::setNumberOfSegments(unsigned int _number) {
		m_NumberSegments = _number;
		regenerateVerticies();
	}

	void CircleShape::setRadius(float _radius) {
		m_Radius = _radius;
		regenerateVerticies();
	}

	void CircleShape::setColour(Colour _colour) {
		m_Colour = _colour;
		regenerateVerticies();
	}

	void CircleShape::regenerateVerticies(void) {
		m_VertexArray = Graphics::VertexArray();

		const float angleOffset = 360.0f / static_cast<float>(m_NumberSegments);
		float accumulatedAngle = 0.0f;
		for (unsigned int i = 0; i < m_NumberSegments; i += 1) {
			m_VertexArray.addVertex(Vertex(
				System::Vector3f(
					std::cosf(accumulatedAngle * 3.14159265f / 180.0f) * m_Radius,
					std::sinf(accumulatedAngle * 3.14159265f / 180.0f) * m_Radius,
					0.0f),
				m_Colour));
			m_VertexArray.addVertex(Vertex(
				System::Vector3f(
					0.0f,
					0.0f,
					0.0f),
				m_Colour));
			m_VertexArray.addVertex(Vertex(
				System::Vector3f(
					std::cosf((accumulatedAngle + angleOffset) * 3.14159265f / 180.0f) * m_Radius,
					std::sinf((accumulatedAngle + angleOffset) * 3.14159265f / 180.0f) * m_Radius,
					0.0f),
				m_Colour));


			accumulatedAngle += angleOffset;
		}

		m_VertexArray.create();
	}
}