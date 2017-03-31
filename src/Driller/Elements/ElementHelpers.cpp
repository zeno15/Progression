#include <Driller/Elements/ElementHelpers.hpp>

#include <Driller/DrillerDefinitions.hpp>
#include <Driller/DrillerResources.hpp>

#include <Window/OpenGL.hpp>


namespace Driller {


	std::vector<float> ElementHelpers::createVerticiesForStaticTexture(const System::Vector2f& _textureId) {
		std::vector<float> data = {
			// TL
			-DrillerDefinitions::TileWidth / 2.0f,
			0.0f,
			(_textureId.x + 0) * DrillerDefinitions::TileWidth / DrillerResources::SpriteSheetSize.x,
			1.0f - (_textureId.y + 0) * DrillerDefinitions::TileHeight / DrillerResources::SpriteSheetSize.y,
			// TR
			+DrillerDefinitions::TileWidth / 2.0f,
			0.0f,
			(_textureId.x + 1) * DrillerDefinitions::TileWidth / DrillerResources::SpriteSheetSize.x,
			1.0f - (_textureId.y + 0) * DrillerDefinitions::TileHeight / DrillerResources::SpriteSheetSize.y,
			// BR
			+DrillerDefinitions::TileWidth / 2.0f,
			-DrillerDefinitions::TileHeight,
			(_textureId.x + 1) * DrillerDefinitions::TileWidth / DrillerResources::SpriteSheetSize.x,
			1.0f - (_textureId.y + 1) * DrillerDefinitions::TileHeight / DrillerResources::SpriteSheetSize.y,


			// TL
			-DrillerDefinitions::TileWidth / 2.0f,
			0.0f,
			(_textureId.x + 0) * DrillerDefinitions::TileWidth / DrillerResources::SpriteSheetSize.x,
			1.0f - (_textureId.y + 0) * DrillerDefinitions::TileHeight / DrillerResources::SpriteSheetSize.y,
			// BR
			+DrillerDefinitions::TileWidth / 2.0f,
			-DrillerDefinitions::TileHeight,
			(_textureId.x + 1) * DrillerDefinitions::TileWidth / DrillerResources::SpriteSheetSize.x,
			1.0f - (_textureId.y + 1) * DrillerDefinitions::TileHeight / DrillerResources::SpriteSheetSize.y,
			// BL
			-DrillerDefinitions::TileWidth / 2.0f,
			-DrillerDefinitions::TileHeight,
			(_textureId.x + 0) * DrillerDefinitions::TileWidth / DrillerResources::SpriteSheetSize.x,
			1.0f - (_textureId.y + 1) * DrillerDefinitions::TileHeight / DrillerResources::SpriteSheetSize.y,
		};

		return data;
	}
	void ElementHelpers::createBasicDoubleTriQuadForTextureId(const System::Vector2f& _textureId, unsigned int *m_VAO, unsigned int *m_VBO) {

		auto data = ElementHelpers::createVerticiesForStaticTexture(_textureId);

		glGenVertexArrays(1, m_VAO);
		glBindVertexArray(*m_VAO);

		glGenBuffers(1, m_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, *m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * data.size(), data.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void *)(0 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void *)(2 * sizeof(float)));
	}
}