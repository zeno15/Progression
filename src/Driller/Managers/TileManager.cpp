#include <Driller/Managers/TileManager.hpp>

#include <Driller/Managers/JobManager.hpp>
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
					Infrastructure::InstanceCollection::getInstance<JobManager>().addJob(ElementHelpers::createBuildElevatorJob(_y));
					auto elevator = drillerGameScene.getElevator(_y);
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
				Infrastructure::InstanceCollection::getInstance<JobManager>().addJob(ElementHelpers::createDigDirtJob(_y, _x));
				tile->setJobQueuedFlag(true);
			}
			else {
				//std::cout << "Activated  tile at x : " << _x << ", y: " << _y << " with no context where one exists and it is clear, do nothing." << std::endl;
			}
		}
	}
}