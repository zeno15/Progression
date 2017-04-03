#include <Driller/Elements/UndergroundTileElement.hpp>

#include <Infrastructure/InstanceCollection.hpp>
#include <Infrastructure/ShaderManager.hpp>
#include <Infrastructure/TextureManager.hpp>

#include <Driller/DrillerDefinitions.hpp>
#include <Driller/DrillerResources.hpp>
#include <Driller/Elements/ElementHelpers.hpp>

#include <Window/OpenGL.hpp>

namespace Driller {

	UndergroundTileElement::UndergroundTileElement(int _column, int _level) :
		m_Level(_level),
		m_Column(_column),
		m_IsClear(false),
		m_HasJobQueued(false),
		m_RoomElement(nullptr) {

		updateBackgroundTexture(DrillerResources::DirtStaticSpriteIndex);
	}
	UndergroundTileElement::~UndergroundTileElement(void) {
		glDeleteBuffers(1, &m_VBO);
		glDeleteVertexArrays(1, &m_VAO);
	}


	void UndergroundTileElement::update(float _delta) {

	}

	bool UndergroundTileElement::handleEvent(const System::Event& _event) {
		return false;
	}

	void UndergroundTileElement::render(const Window::Window& _window, Graphics::RenderData _renderData) const {
		auto& shader = Infrastructure::InstanceCollection::getInstance<Infrastructure::ShaderManager>().getShader(DrillerResources::StaticTexturedShaderName);
		shader.bind();
		shader.passUniform(DrillerResources::StaticTexturedShaderMVPUniformName, _renderData.projection * _renderData.view * System::Mat4x4::createTranslation(System::Vector3f(DrillerDefinitions::TileWidth * static_cast<float>(m_Column), -DrillerDefinitions::TileHeight * static_cast<float>(m_Level), 0.0f)));
		Infrastructure::InstanceCollection::getInstance<Infrastructure::TextureManager>().getTexture(DrillerResources::SpriteSheetName).bind();
		glBindVertexArray(m_VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	void UndergroundTileElement::updateBackgroundTexture(const System::Vector2f& _textureId) {
		glDeleteBuffers(1, &m_VBO);
		glDeleteVertexArrays(1, &m_VAO);

		ElementHelpers::createBasicDoubleTriQuadForTextureId(_textureId, &m_VAO, &m_VBO);
	}

	void UndergroundTileElement::clear(void) {
		m_IsClear = true;
		ElementHelpers::createBasicDoubleTriQuadForTextureId(DrillerResources::EmptyDirtStaticSpriteIndex, &m_VAO, &m_VBO);
	}

	int UndergroundTileElement::getLevel(void) const {
		return m_Level;
	}
	int UndergroundTileElement::getColumn(void) const {
		return m_Column;
	}

	bool UndergroundTileElement::getIsClear(void) const {
		return m_IsClear;
	}

	void UndergroundTileElement::setJobQueuedFlag(bool _flag) {
		m_HasJobQueued = _flag;
	}
	bool UndergroundTileElement::getJobQueued(void) const {
		return m_HasJobQueued;
	}

	RoomElement *UndergroundTileElement::getRoomElement(void) {
		return m_RoomElement;
	}
	void UndergroundTileElement::setRoomElement(RoomElement *_room) {
		m_RoomElement = _room;
	}
}