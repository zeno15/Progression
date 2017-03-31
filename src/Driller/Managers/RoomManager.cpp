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

#include <Driller/Scenes/DrillerGameScene.hpp>

#include <Window/OpenGL.hpp>

#include <iostream>

namespace Driller {
	const std::string RoomManager::Name = "RoomManager";

	RoomManager::RoomManager(void) :
		m_VAO(0),
		m_VBO(0),
		m_DrawingGhost(false),
		m_IsCurrentPositionValid(false) {

	}

	void RoomManager::update(float _delta) {

	}

	bool RoomManager::handleEvent(const System::Event& _event) {
		if (_event.type == System::Event::KeyDown) {
			if (_event.key.key == System::Keyboard::Num1) {
				generateGhost(1);
				return true;
			}
			if (_event.key.key == System::Keyboard::Num2) {
				generateGhost(2);
				return true;
			}
			if (_event.key.key == System::Keyboard::Escape) {
				m_DrawingGhost = false;
				return true;
			}
		}

		if (_event.type == System::Event::MouseButtonPressed) {
			if (m_DrawingGhost) {
				System::Vector2i mousePos(_event.mouseButton.x, _event.mouseButton.y);

				int width = m_CurrentGhostSize.x;
				System::Vector2i drawingOffset;
				if (width % 2 == 1) {
					width -= 1;
					drawingOffset.x -= 1;
				}
				else {
					mousePos.x -= 32;
				}

				auto bottomLeftTile = UserInteractionManager::getTilePositionFromEventCoordinates(mousePos) + drawingOffset;
				auto& drillerGameScene = Infrastructure::InstanceCollection::getInstance<Infrastructure::SceneManager>().getScene<DrillerGameScene>("DrillerGameScene");

				auto isValid = drillerGameScene.isValid(bottomLeftTile, m_CurrentGhostSize);

				if (isValid) {
					std::cout << "Adding room job" << std::endl;

					for (int y = bottomLeftTile.y; y < bottomLeftTile.y + static_cast<int>(m_CurrentGhostSize.y); y += 1) {
						for (int x = bottomLeftTile.x; x < bottomLeftTile.x + static_cast<int>(m_CurrentGhostSize.x); x += 1) {
							drillerGameScene.getTile(x, y)->setJobQueuedFlag(true);
						}
					}
					JobElement job = JobElement("Build", bottomLeftTile, System::Vector2f((bottomLeftTile.x + static_cast<int>(m_CurrentGhostSize.x) / 2) * DrillerDefinitions::TileWidth, DrillerDefinitions::TileHeight * bottomLeftTile.y));
					job.setRemaingTime(8.0f);
					job.onJobComplete.registerCallback([&](const JobElement& _job) {
						std::cout << "Build room job completed at " << _job.getTileCoordinates() << std::endl;
						auto jobCoords = _job.getTileCoordinates();
						m_Rooms.push_back(RoomElement(jobCoords, DrillerResources::MiningSpritePosition, DrillerResources::MiningSpriteSize));
						for (int y = jobCoords.y; y < jobCoords.y + static_cast<int>(DrillerResources::MiningSpriteSize.y); y += 1) {
							for (int x = jobCoords.x; x < jobCoords.x + static_cast<int>(DrillerResources::MiningSpriteSize.x); x += 1) {
								drillerGameScene.getTile(x, y)->setJobQueuedFlag(false);
							}
						}
					});
					Infrastructure::InstanceCollection::getInstance<JobManager>().addJob(job);
					Infrastructure::InstanceCollection::getInstance<UserInteractionManager>().updateCurrentTileInteractionContext(DrillerDefinitions::TileInteractionContext::NoContext);
					m_DrawingGhost = false;
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
			room.render(_window, _renderData);
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

	void RoomManager::generateGhost(unsigned int _index) {
		m_DrawingGhost = true;
		Infrastructure::InstanceCollection::getInstance<UserInteractionManager>().updateCurrentTileInteractionContext(DrillerDefinitions::TileInteractionContext::BuildRoomContext);

		//const System::Vector2u spriteBottomLeft = DrillerResources::DormSpritePosition;
		//m_CurrentGhostSize = DrillerResources::DormSpriteSize; 

		System::Vector2u spriteBottomLeft;

		switch (_index) {
		case 1:
			m_CurrentGhostSize = DrillerResources::DormSpriteSize;
			spriteBottomLeft = DrillerResources::DormSpritePosition;
			break;
		case 2:
			m_CurrentGhostSize = DrillerResources::MiningSpriteSize;
			spriteBottomLeft = DrillerResources::MiningSpritePosition;
			break;
		}

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
}