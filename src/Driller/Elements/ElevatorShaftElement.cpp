#include <Driller/Elements/ElevatorShaftElement.hpp>

#include <Infrastructure/InstanceCollection.hpp>
#include <Infrastructure/ShaderManager.hpp>
#include <Infrastructure/TextureManager.hpp>

#include <Driller/DrillerDefinitions.hpp>
#include <Driller/DrillerResources.hpp>
#include <Driller/Elements/ElementHelpers.hpp>

#include <Window/OpenGL.hpp>

namespace Driller {

	ElevatorShaftElement::ElevatorShaftElement(unsigned int _level) :
		m_Level(_level),
		m_HasJobQueued(false),
		m_IsBuilt(false) {

		ElementHelpers::createBasicDoubleTriQuadForTextureId(DrillerResources::EmptyDirtStaticSpriteIndex, &m_VAO, &m_VBO);
	}

	ElevatorShaftElement::~ElevatorShaftElement(void) {
		glDeleteBuffers(1, &m_VBO);
		glDeleteVertexArrays(1, &m_VAO);
	}


	void ElevatorShaftElement::update(float _delta) {

	}

	bool ElevatorShaftElement::handleEvent(const System::Event& _event) {
		return false;
	}

	void ElevatorShaftElement::render(const Window::Window& _window, Graphics::RenderData _renderData) const {
		auto& shader = Infrastructure::InstanceCollection::getInstance<Infrastructure::ShaderManager>().getShader(DrillerResources::StaticTexturedShaderName);
		shader.bind();
		shader.passUniform(DrillerResources::StaticTexturedShaderMVPUniformName, _renderData.projection * _renderData.view * System::Mat4x4::createTranslation(System::Vector3f(0.0f, -DrillerDefinitions::TileHeight * static_cast<float>(m_Level), 0.0f)));
		Infrastructure::InstanceCollection::getInstance<Infrastructure::TextureManager>().getTexture(DrillerResources::SpriteSheetName).bind();
		glBindVertexArray(m_VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	bool ElevatorShaftElement::isBuilt(void) const {
		return m_IsBuilt;
	}
	void ElevatorShaftElement::setIsBuilt(bool _isBuilt) {
		m_IsBuilt = _isBuilt;

		ElementHelpers::createBasicDoubleTriQuadForTextureId(
			_isBuilt 
			? DrillerResources::ElevatorStaticSpriteIndex 
			: DrillerResources::EmptyDirtStaticSpriteIndex
			, &m_VAO, &m_VBO);
	}

	void ElevatorShaftElement::setJobQueuedFlag(bool _flag) {
		m_HasJobQueued = _flag;
	}
	bool ElevatorShaftElement::getJobQueued(void) const {
		return m_HasJobQueued;
	}
}