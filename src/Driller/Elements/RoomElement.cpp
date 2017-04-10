#include <Driller/Elements/RoomElement.hpp>

#include <Driller/DrillerDefinitions.hpp>
#include <Driller/DrillerResources.hpp>

#include <Infrastructure/InstanceCollection.hpp>
#include <Infrastructure/ShaderManager.hpp>
#include <Infrastructure/TextureManager.hpp>

#include <Window/OpenGL.hpp>

namespace Driller {
	RoomElement::RoomElement(const System::Vector2i& _bottomLeftTile, const System::Vector2i& _spriteSheetPosition, const System::Vector2u& _roomSize) :
		m_BottomLeft(_bottomLeftTile),
		m_SpriteSheetPosition(_spriteSheetPosition),
		m_RoomSize(_roomSize),
		m_Graphics(DrillerResources::SpriteSheetName) {

		m_Graphics.addAnimation(
			System::Vector2f(
				DrillerDefinitions::TileWidth * _roomSize.x,
				DrillerDefinitions::TileHeight * _roomSize.y),
			System::Vector2f(
				DrillerDefinitions::TileWidth * _spriteSheetPosition.x,
				DrillerDefinitions::TileHeight * _spriteSheetPosition.y),
			System::Vector2f(
				DrillerDefinitions::TileWidth * _roomSize.x,
				DrillerDefinitions::TileHeight * _roomSize.y));

		m_Graphics.generate();

		m_Graphics.translate(
			System::Vector2f(
				(static_cast<float>(m_BottomLeft.x) + (static_cast<float>(m_RoomSize.x / 2)) + (m_RoomSize.x % 2 ? 0.0f : -0.5f)) * DrillerDefinitions::TileWidth,
				-(m_BottomLeft.y + 1) * DrillerDefinitions::TileHeight));
	}

	void RoomElement::update(float _delta) {

	}

	bool RoomElement::handleEvent(const System::Event& _event) {
		return false;
	}

	void RoomElement::render(const Window::Window& _window, Graphics::RenderData _renderData) const {

		_renderData.shaderName = DrillerResources::AnimatedSpriteShader;
		_renderData.texture = &Infrastructure::InstanceCollection::getInstance<Infrastructure::TextureManager>().getTexture(DrillerResources::SpriteSheetName);
		_renderData.model.translate(System::Vector3f(0.0f, 0.0f, DrillerDefinitions::BuildingZ));
		m_Graphics.render(_window, _renderData);
	}
	
	const System::Vector2i& RoomElement::getBottomLeftTile(void) const {
		return m_BottomLeft;
	}

	const System::Vector2i& RoomElement::getRoomSize(void) const {
		return m_RoomSize;
	}
}