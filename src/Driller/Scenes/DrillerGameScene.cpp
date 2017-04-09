#include <Driller/Scenes/DrillerGameScene.hpp>

#include <Driller/Managers/JobManager.hpp>
#include <Driller/Managers/NotificationService.hpp>
#include <Driller/Managers/ShuttleManager.hpp>
#include <Driller/Managers/ResourceManager.hpp>
#include <Driller/Managers/RoomManager.hpp>
#include <Driller/Managers/UserInteractionManager.hpp>
#include <Driller/Managers/WorkerManager.hpp>

#include <Infrastructure/Application.hpp>
#include <Infrastructure/Camera.hpp>
#include <Infrastructure/InstanceCollection.hpp>
#include <Infrastructure/ShaderManager.hpp>

#include <Driller/DrillerDefinitions.hpp>
#include <Driller/DrillerResources.hpp>

#include <Window/OpenGL.hpp>

#include <iostream>

namespace Driller {
	DrillerGameScene::DrillerGameScene(void) :
		Infrastructure::Scene("DrillerGameScene") {

		for (int i = 0; i < DrillerDefinitions::MaximumHeight; i += 1) {
			m_ElevatorShafts.push_back(new ElevatorShaftElement(i));
			m_LeftTiles.push_back(std::vector<UndergroundTileElement *>());
			m_RightTiles.push_back(std::vector<UndergroundTileElement *>());
			for (int j = 1; j <= DrillerDefinitions::MaximumWidth; j += 1) {
				m_LeftTiles[i].push_back(new UndergroundTileElement(-j, i));
				m_RightTiles[i].push_back(new UndergroundTileElement(j, i));
			}
		}

		m_ElevatorShafts[0]->setIsBuilt(true);
	}

	DrillerGameScene::~DrillerGameScene(void) {
	}

	
	void DrillerGameScene::update(float _delta) {
		Infrastructure::InstanceCollection::getInstance<RoomManager>().update(_delta);
		Infrastructure::InstanceCollection::getInstance<ShuttleManager>().update(_delta);
		Infrastructure::InstanceCollection::getInstance<WorkerManager>().update(_delta);
	}

	bool DrillerGameScene::handleEvent(const System::Event& _event) {
		if (Infrastructure::InstanceCollection::getInstance<UserInteractionManager>().handleEvent(_event)) {
			return true;
		}

		if (Infrastructure::InstanceCollection::getInstance<Infrastructure::Camera>().handleEvent(_event)) {
			return true;
		}

		if (Infrastructure::InstanceCollection::getInstance<RoomManager>().handleEvent(_event)) {
			return true;
		}

		if (Infrastructure::InstanceCollection::getInstance<WorkerManager>().handleEvent(_event)) {
			return true;
		}
		
		return false;
	}

	void DrillerGameScene::render(const Window::Window& _window, Graphics::RenderData) const {

		auto size = System::Vector2f(Infrastructure::InstanceCollection::getInstance<Infrastructure::Application>().getWindow().getSize());
		auto cameraPosition = Infrastructure::InstanceCollection::getInstance<Infrastructure::Camera>().getPosition();
		auto zoom = Infrastructure::InstanceCollection::getInstance<Infrastructure::Camera>().getZoom();

		System::Mat4x4 view = System::Mat4x4::createTranslation(System::Vector3f(-cameraPosition.x, -cameraPosition.y, 0.0f));
		System::Mat4x4 projection = System::Mat4x4::Orthographic2D(
			-(size.x / 2.0f) / zoom,
			(size.x / 2.0f) / zoom,
			(size.y / 2.0f) / zoom,
			-(size.y / 2.0f) / zoom);

		Graphics::RenderData renderData = Graphics::RenderData(view, projection);

		for (unsigned int i = 0; i < m_LeftTiles.size(); i += 1) {
			for (const auto& tile : m_LeftTiles[i]) {
				tile->render(_window, renderData);
			}
		}

		for (const auto& elevatorShaft : m_ElevatorShafts) {
			elevatorShaft->render(_window, renderData);
		}

		for (unsigned int i = 0; i < m_RightTiles.size(); i += 1) {
			for (const auto& tile : m_RightTiles[i]) {
				tile->render(_window, renderData);
			}
		}

		Infrastructure::InstanceCollection::getInstance<RoomManager>().render(_window, renderData);
		Infrastructure::InstanceCollection::getInstance<WorkerManager>().render(_window, renderData);
		Infrastructure::InstanceCollection::getInstance<ShuttleManager>().render(_window, renderData);
		Infrastructure::InstanceCollection::getInstance<JobManager>().render(_window, renderData);
	}

	ElevatorShaftElement *DrillerGameScene::getElevator(int _level) {
		if (m_ElevatorShafts.size() > static_cast<unsigned int>(_level)) {
			return m_ElevatorShafts[_level];
		}

		return nullptr;
	}

	UndergroundTileElement *DrillerGameScene::getTile(int _column, int _level) {

		if (_column > 0) {
			if (static_cast<unsigned int>(_level) < m_RightTiles.size()) {
				auto& row = m_RightTiles[_level];
				if (static_cast<unsigned int>(std::abs(_column)) < row.size() - 1) {
					return row[std::abs(_column) - 1];
				}
			}
		}
		if (_column < 0) {
			if (static_cast<unsigned int>(_level) < m_LeftTiles.size()) {
				auto& row = m_LeftTiles[_level];
				if (static_cast<unsigned int>(std::abs(_column)) < row.size() - 1) {
					return row[std::abs(_column) - 1];
				}
			}
		}

		return nullptr;
	}

	int DrillerGameScene::getLastBuiltElevatorLevel(void) const {
		int last = -1;
		for (unsigned int i = 0; i < m_ElevatorShafts.size(); i += 1) {
			if (!m_ElevatorShafts[i]->isBuilt()) {
				break;
			}
			last++;
		}
		return last;
	}

	std::vector<UndergroundTileElement *> DrillerGameScene::getTilesFromElevatorToTarget(int _column, int _level) {
		std::vector<UndergroundTileElement *> tiles;
		
		if (_column > 0) {
			for (int c = _column; c > 0; c -= 1) {
				tiles.push_back(getTile(c, _level));
			}
		}
		if (_column < 0) {
			for (int c = _column; c < 0; c += 1) {
				tiles.push_back(getTile(c, _level));
			}
		}

		return tiles;
	}

	bool DrillerGameScene::isValid(const System::Vector2i& _bottomLeftTile, const System::Vector2u& _size) {
		const int startY = _bottomLeftTile.y;
		const int startX = _bottomLeftTile.x;
		const int maxY = _bottomLeftTile.y + _size.y;
		const int maxX = _bottomLeftTile.x + _size.x;

		for (int y = startY; y < maxY; y += 1) {
			for (int x = startX; x < maxX; x += 1) {
				if (x == 0) {
					return false;
				}

				auto tile = getTile(x, y);
				if (!tile->getIsClear() ||
					tile->getJobQueued()) {
					return false;
				}
			}
		}

		return true;
	}
}