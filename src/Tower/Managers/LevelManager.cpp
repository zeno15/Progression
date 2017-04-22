#include <Tower/Managers/LevelManager.hpp>
#include <Tower/Managers/EconomyManager.hpp>

#include <Tower/Components/Tile.hpp>

#include <Tower/GameObjects/Creep.hpp>

#include <Tower/TowerDefinitions.hpp>
#include <Tower/TowerResources.hpp>

#include <Infrastructure/InstanceCollection.hpp>

#include <Graphics/Image.hpp>

#include <iostream>

namespace Tower {
	const std::string LevelManager::Name = "LevelManager";

	LevelManager::LevelManager(void) :
		m_CurrentLevel(nullptr) {

	}
	LevelManager::~LevelManager(void) {

	}

	void LevelManager::update(float _delta) {
		if (m_CurrentLevel != nullptr) {
			m_CurrentLevel->update(_delta);
		}
	}
	bool LevelManager::handleEvent(const System::Event& _event) {
		if (m_CurrentLevel != nullptr) {
			if (m_CurrentLevel->handleEvent(_event)) {
				return true;
			}
		}

		return false;
	}
	void LevelManager::render(const Window::Window& _window, Graphics::RenderData _renderData) const {
		if (m_CurrentLevel != nullptr) {
			m_CurrentLevel->render(_window, _renderData);
		}
	}

	void LevelManager::createNewLevel(void) {
		if (m_CurrentLevel != nullptr) {
			delete m_CurrentLevel;
		}

		unsigned int height = 10;
		unsigned int width = 10;
		std::vector<Tile> tiles;
		for (unsigned int y = 0; y < height; y += 1) {
			for (unsigned int x = 0; x < width; x += 1) {
				tiles.push_back(Tile(x, y));
				
				if (y == 3) {
					tiles[y * width + x].type = Tile::Path;
				}
			}
		}

		m_CurrentLevel = new Level(height, width, tiles);
	}
	void LevelManager::loadLevel(const std::string& _level) {
		const std::string path = TowerResources::LevelDirectoryPath + _level + ".png";

		Graphics::Image level;

		if (!level.loadFromFile(path)) {
			throw std::runtime_error("LevelManager::loadLevel called with invalid level: " + path);
		}

		int width = level.getSize().x;
		int height = level.getSize().y;
		std::vector<Tile> tiles;

		for (int y = 0; y < height; y += 1) {
			for (int x = 0; x < width; x += 1) {
				Tile t(x, y);
				auto colour = level.getPixel(x, height - y - 1);
				if (colour == Graphics::Colour::Red) {
					t.type = Tile::Type::Start;
				}
				else if (colour == Graphics::Colour::Blue) {
					t.type = Tile::Type::End;
				}
				else if (colour == Graphics::Colour::Green) {
					t.type = Tile::Type::Path;
				}
				else {
					t.type = Tile::Type::NonPath;
				}

				tiles.push_back(t);
			}
		}


		Infrastructure::InstanceCollection::getInstance<EconomyManager>().removeMoney(Infrastructure::InstanceCollection::getInstance<EconomyManager>().getMoney());
		Infrastructure::InstanceCollection::getInstance<EconomyManager>().addMoney(100.0f);
		m_CurrentLevel = new Level(width, height, tiles);
	}
	Level& LevelManager::getLevel(void) {
		if (m_CurrentLevel != nullptr) {
			return *m_CurrentLevel;
		}

		throw std::runtime_error("LevelManager::getLevel called when current level is nullptr");
	}
	bool LevelManager::hasLevel(void) const {
		return m_CurrentLevel != nullptr;
	}

	void LevelManager::onCreepReachedEnd(Creep *_creep) {
		m_CurrentLevel->reduceLivesRemaining(_creep->getLivesCost());
	}
	void LevelManager::onCreepKilled(Creep *_creep) {

	}
}