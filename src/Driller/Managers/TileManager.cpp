#include <Driller/Managers/TileManager.hpp>

#include <Driller/Managers/NotificationService.hpp>
#include <Driller/Managers/JobManager.hpp>
#include <Driller/Managers/ResourceManager.hpp>
#include <Driller/Managers/RoomManager.hpp>

#include <Driller/Elements/ElementHelpers.hpp>

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
		case DrillerDefinitions::TileInteractionContext::ResetContext:
			handleResetContextInteraction(_x, _y);
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
						if (Infrastructure::InstanceCollection::getInstance<ResourceManager>().getMoney() >= DrillerDefinitions::BuildElevatorCost) {
							Infrastructure::InstanceCollection::getInstance<ResourceManager>().removeMoney(DrillerDefinitions::BuildElevatorCost);
							Infrastructure::InstanceCollection::getInstance<JobManager>().addJob(ElementHelpers::createBuildElevatorJob(_y));
							auto elevator = drillerGameScene.getElevator(_y);
							elevator->setJobQueuedFlag(true);
						}
						else {
							std::cout << "Cannot afford $" << DrillerDefinitions::BuildElevatorCost << " for elevator, only have $" << Infrastructure::InstanceCollection::getInstance<ResourceManager>().getMoney() << std::endl;
						}
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
				if (Infrastructure::InstanceCollection::getInstance<ResourceManager>().getMoney() >= DrillerDefinitions::DigDirtCost) {
					Infrastructure::InstanceCollection::getInstance<ResourceManager>().removeMoney(DrillerDefinitions::DigDirtCost);
					Infrastructure::InstanceCollection::getInstance<JobManager>().addJob(ElementHelpers::createDigDirtJob(_y, _x));
					tile->setJobQueuedFlag(true);
				}
				else {
					std::cout << "Cannot afford $" << DrillerDefinitions::DigDirtCost << " for dig dirt, only have $" << Infrastructure::InstanceCollection::getInstance<ResourceManager>().getMoney() << std::endl;
				}
			}
			else {
				//std::cout << "Activated  tile at x : " << _x << ", y: " << _y << " with no context where one exists and it is clear, do nothing." << std::endl;
			}
		}
	}

	void TileManager::handleResetContextInteraction(int _x, int _y) {
		auto& drillerGameScene = Infrastructure::InstanceCollection::getInstance<Infrastructure::SceneManager>().getScene<DrillerGameScene>("DrillerGameScene");
		auto& tileManager = Infrastructure::InstanceCollection::getInstance<TileManager>();
		auto& roomManager = Infrastructure::InstanceCollection::getInstance<RoomManager>();
		auto& jobManager = Infrastructure::InstanceCollection::getInstance<JobManager>();

		if (_x == 0) {
			auto e = drillerGameScene.getElevator(_y);
			if (e->isBuilt()) {
				e->setIsBuilt(false);
			}
		}
		else {
			auto t = drillerGameScene.getTile(_x, _y);
			t->setJobQueuedFlag(false);
			t->reset();
		}

		auto jobs = jobManager.getJobsThatContainTile(System::Vector2i(_x, _y));

		for (auto job : jobs) {
			jobManager.cancelJob(job);
		}

		auto room = roomManager.getRoomAtTile(System::Vector2i(_x, _y));

		if (room != nullptr) {
			auto sizeIncrease = System::Vector2i(room->getRoomSize()) - System::Vector2i(1, 1);
			auto start = room->getBottomLeftTile();
			for (int y = start.y; y <= start.y + sizeIncrease.y; y += 1) {
				for (int x = start.x; x <= start.x + sizeIncrease.x; x += 1) {
					auto t = drillerGameScene.getTile(_x, _y);
					t->setJobQueuedFlag(false);
					t->clear();
				}
			}

			roomManager.removeRoom(room);
		}
	}
}