#include <Driller/Elements/ElementHelpers.hpp>

#include <Driller/DrillerDefinitions.hpp>
#include <Driller/DrillerResources.hpp>

#include <Driller/Managers/JobManager.hpp>
#include <Driller/Managers/RoomManager.hpp>

#include <Driller/Scenes/DrillerGameScene.hpp>

#include <Infrastructure/InstanceCollection.hpp>
#include <Infrastructure/SceneManager.hpp>

#include <Window/OpenGL.hpp>

#include <iostream>

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

	JobElement *ElementHelpers::createBuildElevatorJob(int _level) {
		auto job = new JobElement(JobContextInfo(JobContextInfo::BuildElevatorJob(_level)), System::Vector2i(0, _level), System::Vector2f(0 * DrillerDefinitions::TileWidth, (_level - 1) * DrillerDefinitions::TileHeight));
		job->setRemaingTime(3.0f);
		job->onJobComplete.registerCallback([](JobElement *_job) {
			std::cout << "Build Elevator job at x: " << _job->getTileCoordinates().x << ", y: " << _job->getTileCoordinates().y << " is complete" << std::endl;
			auto& drillerGameScene = Infrastructure::InstanceCollection::getInstance<Infrastructure::SceneManager>().getScene<DrillerGameScene>("DrillerGameScene");
			auto elevator = drillerGameScene.getElevator(_job->getTileCoordinates().y);
			elevator->setIsBuilt(true);
			elevator->setJobQueuedFlag(false);
		});

		return job;
	}
	JobElement *ElementHelpers::createDigDirtJob(int _level, int _column) {
		auto job = new JobElement(JobContextInfo(JobContextInfo::DigDirtJob(_column, _level)), System::Vector2i(_column, _level));
		job->setRemaingTime(2.0f);
		if (_column > 0) {
			job->m_WorkPosition = System::Vector2f((static_cast<float>(_column) - 0.9f) * DrillerDefinitions::TileWidth, _level * DrillerDefinitions::TileWidth);
		}
		else {
			job->m_WorkPosition = System::Vector2f((static_cast<float>(_column) + 0.9f) * DrillerDefinitions::TileWidth, _level * DrillerDefinitions::TileWidth);
		}
		job->onJobComplete.registerCallback([](JobElement *_job) {
			std::cout << "Dig dirt job at x: " << _job->getTileCoordinates().x << ", y: " << _job->getTileCoordinates().y << " is complete" << std::endl;
			auto& drillerGameScene = Infrastructure::InstanceCollection::getInstance<Infrastructure::SceneManager>().getScene<DrillerGameScene>("DrillerGameScene");
			auto tile = drillerGameScene.getTile(_job->getTileCoordinates().x, _job->getTileCoordinates().y);
			tile->clear();
			tile->setJobQueuedFlag(false);
		});

		return job;
	}
	JobElement *ElementHelpers::createBuildRoomJob(const JobContextInfo& _contextInfo) {
		auto position = DrillerDefinitions::RoomData[_contextInfo.BuildRoomData.type][DrillerDefinitions::RoomInfo::SpritePosition];
		auto size = DrillerDefinitions::RoomData[_contextInfo.BuildRoomData.type][DrillerDefinitions::RoomInfo::SpriteSize];

		System::Vector2i tilePosition = System::Vector2i(_contextInfo.BuildRoomData.column, _contextInfo.BuildRoomData.level);
		System::Vector2f workPosition = System::Vector2f(tilePosition.x * DrillerDefinitions::TileWidth, tilePosition.y * DrillerDefinitions::TileHeight) +
										System::Vector2f((size.x - 1) * DrillerDefinitions::TileWidth / 2.0f, 0.0f);

		auto job = new JobElement(_contextInfo, tilePosition, workPosition);
		job->setRemaingTime(5.0f);
		job->onJobComplete.registerCallback([&](JobElement *_job) {
			std::cout << "Build room job completed at " << _job->getTileCoordinates() << std::endl;
			auto jobCoords = _job->getTileCoordinates();

			RoomElement *room = new RoomElement(
				jobCoords,
				DrillerDefinitions::RoomData[_job->getJobInfo().BuildRoomData.type][DrillerDefinitions::RoomInfo::SpritePosition],
				DrillerDefinitions::RoomData[_job->getJobInfo().BuildRoomData.type][DrillerDefinitions::RoomInfo::SpriteSize]);

			Infrastructure::InstanceCollection::getInstance<RoomManager>().addRoom(room);
			auto& drillerGameScene = Infrastructure::InstanceCollection::getInstance<Infrastructure::SceneManager>().getScene<DrillerGameScene>("DrillerGameScene");

			for (int y = jobCoords.y; y < jobCoords.y + DrillerDefinitions::RoomData[_job->getJobInfo().BuildRoomData.type][DrillerDefinitions::RoomInfo::SpriteSize].y; y += 1) {
				for (int x = jobCoords.x; x < jobCoords.x + DrillerDefinitions::RoomData[_job->getJobInfo().BuildRoomData.type][DrillerDefinitions::RoomInfo::SpriteSize].x; x += 1) {
					drillerGameScene.getTile(x, y)->setJobQueuedFlag(false);
					drillerGameScene.getTile(x, y)->setRoomElement(room);
				}
			}
		});

		return job;
	}
}