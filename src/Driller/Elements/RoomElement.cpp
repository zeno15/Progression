#include <Driller/Elements/RoomElement.hpp>

#include <Driller/DrillerDefinitions.hpp>
#include <Driller/DrillerResources.hpp>

#include <Infrastructure/InstanceCollection.hpp>
#include <Infrastructure/ShaderManager.hpp>
#include <Infrastructure/TextureManager.hpp>

#include <Window/OpenGL.hpp>

namespace Driller {
	RoomElement::RoomElement(const System::Vector2i& _bottomLeftTile, const System::Vector2i& _spriteSheetPosition, const System::Vector2u& _roomSize) :
		m_VAO(0),
		m_VBO(0),
		m_BottomLeft(_bottomLeftTile),
		m_SpriteSheetPosition(_spriteSheetPosition),
		m_RoomSize(_roomSize) {

		generateGraphics();
	}

	void RoomElement::update(float _delta) {

	}

	bool RoomElement::handleEvent(const System::Event& _event) {
		return false;
	}

	void RoomElement::render(const Window::Window& _window, Graphics::RenderData _renderData) const {

		auto& shader = Infrastructure::InstanceCollection::getInstance<Infrastructure::ShaderManager>().getShader(DrillerResources::StaticTexturedShaderName);
		shader.bind();
		shader.passUniform(DrillerResources::StaticTexturedShaderMVPUniformName,
			_renderData.projection *
			_renderData.view *
			System::Mat4x4::createTranslation(System::Vector3f(
				DrillerDefinitions::TileWidth * m_BottomLeft.x,
				-DrillerDefinitions::TileHeight * m_BottomLeft.y,
				0.45f)));

		Infrastructure::InstanceCollection::getInstance<Infrastructure::TextureManager>().getTexture(DrillerResources::SpriteSheetName).bind();
		glBindVertexArray(m_VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	void RoomElement::generateGraphics(void) {
		std::vector<float> data = {
			// TL
			-DrillerDefinitions::TileWidth / 2.0f,
			0.0f,
			static_cast<float>(m_SpriteSheetPosition.x + 0) * DrillerDefinitions::TileWidth / DrillerResources::SpriteSheetSize.x,
			1.0f - static_cast<float>(m_SpriteSheetPosition.y + 0) * DrillerDefinitions::TileHeight / DrillerResources::SpriteSheetSize.y,
			// TR
			DrillerDefinitions::TileWidth * m_RoomSize.x - DrillerDefinitions::TileWidth / 2.0f,
			0.0f,
			static_cast<float>(m_SpriteSheetPosition.x + m_RoomSize.x) * DrillerDefinitions::TileWidth / DrillerResources::SpriteSheetSize.x,
			1.0f - static_cast<float>(m_SpriteSheetPosition.y + 0) * DrillerDefinitions::TileHeight / DrillerResources::SpriteSheetSize.y,
			// BR
			DrillerDefinitions::TileWidth * m_RoomSize.x - DrillerDefinitions::TileWidth / 2.0f,
			-DrillerDefinitions::TileHeight * m_RoomSize.y,
			(m_SpriteSheetPosition.x + m_RoomSize.x) * DrillerDefinitions::TileWidth / DrillerResources::SpriteSheetSize.x,
			1.0f - static_cast<float>(m_SpriteSheetPosition.y + m_RoomSize.y) * DrillerDefinitions::TileHeight / DrillerResources::SpriteSheetSize.y,


			// TL
			-DrillerDefinitions::TileWidth / 2.0f,
			0.0f,
			static_cast<float>(m_SpriteSheetPosition.x + 0) * DrillerDefinitions::TileWidth / DrillerResources::SpriteSheetSize.x,
			1.0f - static_cast<float>(m_SpriteSheetPosition.y + 0) * DrillerDefinitions::TileHeight / DrillerResources::SpriteSheetSize.y,
			// BR
			DrillerDefinitions::TileWidth * m_RoomSize.x - DrillerDefinitions::TileWidth / 2.0f,
			-DrillerDefinitions::TileHeight * m_RoomSize.y,
			static_cast<float>(m_SpriteSheetPosition.x + m_RoomSize.x) * DrillerDefinitions::TileWidth / DrillerResources::SpriteSheetSize.x,
			1.0f - static_cast<float>(m_SpriteSheetPosition.y + m_RoomSize.y) * DrillerDefinitions::TileHeight / DrillerResources::SpriteSheetSize.y,
			// BL
			-DrillerDefinitions::TileWidth / 2.0f,
			-DrillerDefinitions::TileHeight * m_RoomSize.y,
			static_cast<float>(m_SpriteSheetPosition.x + 0) * DrillerDefinitions::TileWidth / DrillerResources::SpriteSheetSize.x,
			1.0f - static_cast<float>(m_SpriteSheetPosition.y + m_RoomSize.y) * DrillerDefinitions::TileHeight / DrillerResources::SpriteSheetSize.y,
		};

		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);

		glGenBuffers(1, &m_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * data.size(), data.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void *)(0 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void *)(2 * sizeof(float)));
	}
	
	const System::Vector2i& RoomElement::getBottomLeftTile(void) const {
		return m_BottomLeft;
	}

	const System::Vector2i& RoomElement::getRoomSize(void) const {
		return System::Vector2i(m_RoomSize);
	}
}