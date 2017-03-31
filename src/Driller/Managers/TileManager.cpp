#include <Driller/Managers/TileManager.hpp>

#include <Driller/Managers/JobManager.hpp>
#include <Driller/Managers/RoomManager.hpp>

#include <Driller/Scenes/DrillerGameScene.hpp>

#include <Infrastructure/InstanceCollection.hpp>
#include <Infrastructure/SceneManager.hpp>

#include <iostream>
#include <cassert>

namespace Driller {
	const std::string TileManager::Name = "TileManager";

	void TileManager::onTileActivated(int _x, int _y, DrillerDefinitions::TileInteractionContext _context) {

		switch (_context) {
		case DrillerDefinitions::TileInteractionContext::NoContext:
			handleNoContextInteraction(_x, _y);
			break;
		default:
			std::cout << "Activated tile (" << _x << "," << _y << ") with unhandled context '" << _context << "'" << std::endl;
			break;
		}
	}

	void TileManager::handleNoContextInteraction(int _x, int _y) {
		auto& drillerGameScene = Infrastructure::InstanceCollection::getInstance<Infrastructure::SceneManager>().getScene<DrillerGameScene>("DrillerGameScene");

		if (_x == 0) {
			auto elevator = drillerGameScene.getElevator(_y);

			assert(elevator != nullptr);

			if (!elevator->isBuilt()) {
				auto lastBuilt = drillerGameScene.getLastBuiltElevatorLevel();
				if (lastBuilt + 1 == _y) {
					auto elevator = drillerGameScene.getElevator(_y);
					// Enque create elevator job.
					auto job = JobElement("BuildElevator", System::Vector2i(_x, _y), System::Vector2f(_x * DrillerDefinitions::TileWidth, (_y - 1) * DrillerDefinitions::TileHeight));
					job.setRemaingTime(5.0f);
					job.onJobComplete.registerCallback([](const JobElement& _job) {
						std::cout << "Build Elevator job at x: " << _job.getTileCoordinates().x << ", y: " << _job.getTileCoordinates().y << " is complete" << std::endl;
						auto& drillerGameScene = Infrastructure::InstanceCollection::getInstance<Infrastructure::SceneManager>().getScene<DrillerGameScene>("DrillerGameScene");
						auto elevator = drillerGameScene.getElevator(_job.getTileCoordinates().y);
						elevator->setIsBuilt(true);
						elevator->setJobQueuedFlag(false);
					});
					Infrastructure::InstanceCollection::getInstance<JobManager>().addJob(job);
					elevator->setJobQueuedFlag(true);
				}
				else {
					//std::cout << "Cant create new elevator at x: " << _x << ", y: " << _y << " need to build before it." << std::endl;
				}
			}
			else {
				//std::cout << "We activated an existing elevator at x: " << _x << ", y: " << _y << ", and it already exists, activate as a room." << std::endl;
			}
		}
		else {
			auto tile = drillerGameScene.getTile(_x, _y);

			assert(tile != nullptr);

			if (!tile->getIsClear() && !tile->getJobQueued()) {
				// Enque dig/clear job.
				auto job = JobElement("DigDirt", System::Vector2i(_x, _y));
				job.setRemaingTime(2.0f);
				if (_x > 0) {
					job.m_WorkPosition = System::Vector2f((static_cast<float>(_x) - 0.9f) * DrillerDefinitions::TileWidth, _y * DrillerDefinitions::TileWidth);
				}
				else {
					job.m_WorkPosition = System::Vector2f((static_cast<float>(_x) + 0.9f) * DrillerDefinitions::TileWidth, _y * DrillerDefinitions::TileWidth);
				}
				job.onJobComplete.registerCallback([](const JobElement& _job) {
					std::cout << "Dig dirt job at x: " << _job.getTileCoordinates().x << ", y: " << _job.getTileCoordinates().y << " is complete" << std::endl;
					auto& drillerGameScene = Infrastructure::InstanceCollection::getInstance<Infrastructure::SceneManager>().getScene<DrillerGameScene>("DrillerGameScene");
					auto tile = drillerGameScene.getTile(_job.getTileCoordinates().x, _job.getTileCoordinates().y);
					tile->clear();
					tile->setJobQueuedFlag(false);
				});
				Infrastructure::InstanceCollection::getInstance<JobManager>().addJob(job);
				tile->setJobQueuedFlag(true);
			}
			else {
				//std::cout << "Activated  tile at x : " << _x << ", y: " << _y << " with no context where one exists and it is clear, do nothing." << std::endl;
			}
		}
	}
}