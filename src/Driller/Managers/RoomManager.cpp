#include <Driller/Managers/RoomManager.hpp>

#include <Driller/Managers/UserInteractionManager.hpp>
#include <Driller/Managers/JobManager.hpp>

#include <Infrastructure/InstanceCollection.hpp>
#include <Infrastructure/SceneManager.hpp>
#include <Infrastructure/ShaderManager.hpp>
#include <Infrastructure/TextureManager.hpp>

#include <Driller/DrillerDefinitions.hpp>
#include <Driller/DrillerResources.hpp>

#include <Driller/Elements/JobElement.hpp>
#include <Driller/Elements/ElementHelpers.hpp>

#include <Driller/Scenes/DrillerGameScene.hpp>

#include <Window/OpenGL.hpp>

#include <iostream>

namespace Driller {
	const std::string RoomManager::Name = "RoomManager";

	RoomManager::RoomManager(void) :
		m_VAO(0),
		m_VBO(0),
		m_DrawingGhost(false),
		m_IsCurrentPositionValid(false),
		m_CurrentRoom(DrillerDefinitions::RoomType::None){

	}

	void RoomManager::update(float _delta) {
		for (auto& room : m_Rooms) {
			room->update(_delta);
		}
	}

	bool RoomManager::handleEvent(const System::Event& _event) {
		if (_event.type == System::Event::KeyDown) {
			if (_event.key.key == System::Keyboard::Num1) {
				generateGhost(DrillerDefinitions::RoomType::Dorm);
				return true;
			}
			if (_event.key.key == System::Keyboard::Num2) {
				generateGhost(DrillerDefinitions::RoomType::Mining);
				return true;
			}
			if (_event.key.key == System::Keyboard::Escape) {
				m_DrawingGhost = false;
				m_CurrentRoom = DrillerDefinitions::RoomType::None;
				return true;
			}
		}

		if (_event.type == System::Event::MouseButtonPressed) {
			if (_event.mouseButton.button == System::Mouse::Left && m_DrawingGhost) {
				System::Vector2i mousePos(_event.mouseButton.x, _event.mouseButton.y);

				int width = m_CurrentGhostSize.x;
				System::Vector2i drawingOffset;
				if (width % 2 == 1) {
					width -= 1;
					drawingOffset.x -= 1;
				}
				else {
					mousePos.x -= static_cast<int>(DrillerDefinitions::TileWidth) / 2;
				}

				auto bottomLeftTile = UserInteractionManager::getTilePositionFromEventCoordinates(mousePos) + drawingOffset;
				auto& drillerGameScene = Infrastructure::InstanceCollection::getInstance<Infrastructure::SceneManager>().getScene<DrillerGameScene>("DrillerGameScene");

				auto isValid = drillerGameScene.isValid(bottomLeftTile, m_CurrentGhostSize);

				if (isValid) {
					for (int y = bottomLeftTile.y; y < bottomLeftTile.y + static_cast<int>(m_CurrentGhostSize.y); y += 1) {
						for (int x = bottomLeftTile.x; x < bottomLeftTile.x + static_cast<int>(m_CurrentGhostSize.x); x += 1) {
							drillerGameScene.getTile(x, y)->setJobQueuedFlag(true);
						}
					}				

					auto contextInfo = JobContextInfo(JobContextInfo::BuildRoomJob(bottomLeftTile.x, bottomLeftTile.y, m_CurrentRoom));

					auto job = ElementHelpers::createBuildRoomJob(contextInfo);

					Infrastructure::InstanceCollection::getInstance<JobManager>().addJob(job);
					resetFromDrawingGhost();
				}

				return true;
			}
		}

		if (_event.type == System::Event::MouseMoved) {
			if (m_DrawingGhost) {
				System::Vector2i mousePos(_event.position.x, _event.position.y);


				int width = m_CurrentGhostSize.x;
				System::Vector2i drawingOffset;
				if (width % 2 == 1) {
					width -= 1;
					drawingOffset.x -= 1;
				}
				else {
					mousePos.x -= 32;
				}

				m_BottomLeftTile = UserInteractionManager::getTilePositionFromEventCoordinates(mousePos) + drawingOffset;
				auto& drillerGameScene = Infrastructure::InstanceCollection::getInstance<Infrastructure::SceneManager>().getScene<DrillerGameScene>("DrillerGameScene");

				m_IsCurrentPositionValid = drillerGameScene.isValid(m_BottomLeftTile, m_CurrentGhostSize);
			}
		}
		return false;
	}

	void RoomManager::render(const Window::Window& _window, Graphics::RenderData _renderData) const {
		for (auto& room : m_Rooms) {
			room->render(_window, _renderData);
		}


		if (m_DrawingGhost) {
			auto& shader = Infrastructure::InstanceCollection::getInstance<Infrastructure::ShaderManager>().getShader(DrillerResources::BuildingGhostShaderName);
			shader.bind();
			shader.passUniform(DrillerResources::BuildingGhostShaderColourUniformName, m_IsCurrentPositionValid ? Graphics::Colour::Green : Graphics::Colour::Red);
			shader.passUniform(DrillerResources::StaticTexturedShaderMVPUniformName, 
				_renderData.projection * 
				_renderData.view * 
				System::Mat4x4::createTranslation(System::Vector3f(
					DrillerDefinitions::TileWidth * m_BottomLeftTile.x,
					-DrillerDefinitions::TileHeight * m_BottomLeftTile.y,
					0.5f)));

			Infrastructure::InstanceCollection::getInstance<Infrastructure::TextureManager>().getTexture(DrillerResources::SpriteSheetName).bind();
			glBindVertexArray(m_VAO);
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}
	}

	void RoomManager::generateGhost(DrillerDefinitions::RoomType _roomType) {
		m_CurrentRoom = _roomType;
		m_DrawingGhost = true;
		Infrastructure::InstanceCollection::getInstance<UserInteractionManager>().updateCurrentTileInteractionContext(DrillerDefinitions::TileInteractionContext::BuildRoomContext);

		System::Vector2i spriteBottomLeft = m_CurrentGhostSize = DrillerDefinitions::RoomData[m_CurrentRoom][DrillerDefinitions::RoomInfo::SpritePosition];;
		m_CurrentGhostSize = m_CurrentGhostSize = DrillerDefinitions::RoomData[m_CurrentRoom][DrillerDefinitions::RoomInfo::SpriteSize];

		std::vector<float> data = {
			// TL
			- DrillerDefinitions::TileWidth / 2.0f,
			0.0f,
			static_cast<float>(spriteBottomLeft.x + 0) * DrillerDefinitions::TileWidth / DrillerResources::SpriteSheetSize.x,
			1.0f - static_cast<float>(spriteBottomLeft.y + 0) * DrillerDefinitions::TileHeight / DrillerResources::SpriteSheetSize.y,
			// TR
			DrillerDefinitions::TileWidth * m_CurrentGhostSize.x - DrillerDefinitions::TileWidth / 2.0f,
			0.0f,
			static_cast<float>(spriteBottomLeft.x + m_CurrentGhostSize.x) * DrillerDefinitions::TileWidth / DrillerResources::SpriteSheetSize.x,
			1.0f - static_cast<float>(spriteBottomLeft.y + 0) * DrillerDefinitions::TileHeight / DrillerResources::SpriteSheetSize.y,
			// BR
			DrillerDefinitions::TileWidth * m_CurrentGhostSize.x - DrillerDefinitions::TileWidth / 2.0f,
			-DrillerDefinitions::TileHeight * m_CurrentGhostSize.y,
			(spriteBottomLeft.x + m_CurrentGhostSize.x) * DrillerDefinitions::TileWidth / DrillerResources::SpriteSheetSize.x,
			1.0f - static_cast<float>(spriteBottomLeft.y + m_CurrentGhostSize.y) * DrillerDefinitions::TileHeight / DrillerResources::SpriteSheetSize.y,


			// TL
			-DrillerDefinitions::TileWidth / 2.0f,
			0.0f,
			static_cast<float>(spriteBottomLeft.x + 0) * DrillerDefinitions::TileWidth / DrillerResources::SpriteSheetSize.x,
			1.0f - static_cast<float>(spriteBottomLeft.y + 0) * DrillerDefinitions::TileHeight / DrillerResources::SpriteSheetSize.y,
			// BR
			DrillerDefinitions::TileWidth * m_CurrentGhostSize.x - DrillerDefinitions::TileWidth / 2.0f,
			-DrillerDefinitions::TileHeight * m_CurrentGhostSize.y,
			static_cast<float>(spriteBottomLeft.x + m_CurrentGhostSize.x) * DrillerDefinitions::TileWidth / DrillerResources::SpriteSheetSize.x,
			1.0f - static_cast<float>(spriteBottomLeft.y + m_CurrentGhostSize.y) * DrillerDefinitions::TileHeight / DrillerResources::SpriteSheetSize.y,
			// BL
			-DrillerDefinitions::TileWidth / 2.0f,
			-DrillerDefinitions::TileHeight * m_CurrentGhostSize.y,
			static_cast<float>(spriteBottomLeft.x + 0) * DrillerDefinitions::TileWidth / DrillerResources::SpriteSheetSize.x,
			1.0f - static_cast<float>(spriteBottomLeft.y + m_CurrentGhostSize.y) * DrillerDefinitions::TileHeight / DrillerResources::SpriteSheetSize.y,
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

	void RoomManager::addRoom(RoomElement *_room) {
		m_Rooms.push_back(_room);
		_room->onRoomCreated();
	}
	void RoomManager::removeRoom(RoomElement *_room) {
		for (unsigned int i = 0; i < m_Rooms.size(); i += 1) {
			if (_room == m_Rooms[i]) {
				_room->onRoomRemoved();
				delete _room;
				m_Rooms.erase(m_Rooms.begin() + i);
				return;
			}
		}
	}
	void RoomManager::resetFromDrawingGhost(void) {
		Infrastructure::InstanceCollection::getInstance<UserInteractionManager>().updateCurrentTileInteractionContext(DrillerDefinitions::TileInteractionContext::NoContext);
		m_DrawingGhost = false;
		m_CurrentRoom = DrillerDefinitions::RoomType::None;
	}

	RoomElement *RoomManager::getRoomAtTile(const System::Vector2i& _tileCoordinates) {
		for (auto& room : m_Rooms) {
			auto sizeIncrease = System::Vector2i(room->getRoomSize()) - System::Vector2i(1, 1);
			auto start = room->getBottomLeftTile();

			if (start.x <= _tileCoordinates.x && _tileCoordinates.x <= start.x + sizeIncrease.x &&
				start.y <= _tileCoordinates.y && _tileCoordinates.y <= start.y + sizeIncrease.y) {
				return room;
			}
		}

		return nullptr;
	}
}