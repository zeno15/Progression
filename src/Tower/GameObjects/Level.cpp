#include <Tower/GameObjects/Level.hpp>

#include <Tower/TowerDefinitions.hpp>
#include <Tower/TowerResources.hpp>

#include <Tower/Managers/LevelManager.hpp>
#include <Tower/Managers/NotificationManager.hpp>

#include <Infrastructure/InstanceCollection.hpp>
#include <Infrastructure/ShaderManager.hpp>

#include <Window/OpenGL.hpp>

#include <iostream>
#include <cassert>

namespace Tower {

	Level::Level(void) :
		Level(10, 10) {

	}
	Level::Level(unsigned int _width, unsigned int _height) :
		width(_width),
		height(_height),
		m_LivesRemaining(10) {

		for (unsigned int y = 0; y < _height; y += 1) {
			for (unsigned int x = 0; x < _width; x += 1) {
				m_Tiles.emplace_back(x, y);

				m_TileGraphics.addVertex(Graphics::Vertex(
					System::Vector3f(
						TowerDefinitions::TileSize * (x + 0),
						TowerDefinitions::TileSize * (y + 0),
						0.0f),
					Graphics::Colour::White));

				m_TileGraphics.addVertex(Graphics::Vertex(
					System::Vector3f(
						TowerDefinitions::TileSize * (x + 1),
						TowerDefinitions::TileSize * (y + 0),
						0.0f),
					Graphics::Colour::White));

				m_TileGraphics.addVertex(Graphics::Vertex(
					System::Vector3f(
						TowerDefinitions::TileSize * (x + 1),
						TowerDefinitions::TileSize * (y + 1),
						0.0f),
					Graphics::Colour::White));



				m_TileGraphics.addVertex(Graphics::Vertex(
					System::Vector3f(
						TowerDefinitions::TileSize * (x + 0),
						TowerDefinitions::TileSize * (y + 0),
						0.0f),
					Graphics::Colour::Green));

				m_TileGraphics.addVertex(Graphics::Vertex(
					System::Vector3f(
						TowerDefinitions::TileSize * (x + 1),
						TowerDefinitions::TileSize * (y + 1),
						0.0f),
					Graphics::Colour::Green));

				m_TileGraphics.addVertex(Graphics::Vertex(
					System::Vector3f(
						TowerDefinitions::TileSize * (x + 0),
						TowerDefinitions::TileSize * (y + 1),
						0.0f),
					Graphics::Colour::Green));
			}
		}

		m_TileGraphics.create();
	}

	Level::Level(unsigned int _width, unsigned int _height, std::vector<Tile>& _tiles) :
		width(_width),
		height(_height),
		m_Tiles(_tiles),
		m_LivesRemaining(10) {

		assert(_tiles.size() == _width * _height);

		for (unsigned int y = 0; y < _height; y += 1) {
			for (unsigned int x = 0; x < _width; x += 1) {
				auto& tile = m_Tiles[y * width + x];

				m_TileGraphics.addVertex(Graphics::Vertex(
					System::Vector3f(
						TowerDefinitions::TileSize * (x + 0),
						TowerDefinitions::TileSize * (y + 0),
						0.0f),
					tile.getBaseColourForTile()));

				m_TileGraphics.addVertex(Graphics::Vertex(
					System::Vector3f(
						TowerDefinitions::TileSize * (x + 1),
						TowerDefinitions::TileSize * (y + 0),
						0.0f),
					tile.getBaseColourForTile()));

				m_TileGraphics.addVertex(Graphics::Vertex(
					System::Vector3f(
						TowerDefinitions::TileSize * (x + 1),
						TowerDefinitions::TileSize * (y + 1),
						0.0f),
					tile.getBaseColourForTile()));



				m_TileGraphics.addVertex(Graphics::Vertex(
					System::Vector3f(
						TowerDefinitions::TileSize * (x + 0),
						TowerDefinitions::TileSize * (y + 0),
						0.0f),
					tile.getBaseColourForTile()));

				m_TileGraphics.addVertex(Graphics::Vertex(
					System::Vector3f(
						TowerDefinitions::TileSize * (x + 1),
						TowerDefinitions::TileSize * (y + 1),
						0.0f),
					tile.getBaseColourForTile()));

				m_TileGraphics.addVertex(Graphics::Vertex(
					System::Vector3f(
						TowerDefinitions::TileSize * (x + 0),
						TowerDefinitions::TileSize * (y + 1),
						0.0f),
					tile.getBaseColourForTile()));
			}
		}

		m_TileGraphics.create();

		generateLevelPaths();

	}
	Level::~Level(void) {

	}

	void Level::update(float _delta) {

	}
	bool Level::handleEvent(const System::Event& _event) {
		return false;
	}
	void Level::render(const Window::Window& _window, Graphics::RenderData _renderData) const {
		auto& shader = Infrastructure::InstanceCollection::getInstance<Infrastructure::ShaderManager>().getShader(TowerResources::VertexArrayNoTextureShaderName);
		shader.bind();
		shader.passUniform(TowerResources::VertexArrayNoTextureShaderUniformMVP,
			_renderData.projection *
			_renderData.view *
			System::Mat4x4::createTranslation(System::Vector3f(0.0f, 0.0f, TowerDefinitions::BackgroundZ)));

		m_TileGraphics.render(_window, _renderData);

		auto lines = Graphics::VertexArray();
		
		for (auto& t : m_Tiles) {
			lines.addVertex(
				Graphics::Vertex(
					System::Vector3f(
						t.x * TowerDefinitions::TileSize + TowerDefinitions::TileSize / 2.0f,
						t.y * TowerDefinitions::TileSize + TowerDefinitions::TileSize / 2.0f,
						TowerDefinitions::ProjectileZ),
					Graphics::Colour::Yellow));
			lines.addVertex(
				Graphics::Vertex(
					System::Vector3f(
						t.x * TowerDefinitions::TileSize + TowerDefinitions::TileSize / 2.0f + 4.0f,
						t.y * TowerDefinitions::TileSize + TowerDefinitions::TileSize / 2.0f + 4.0f,
						TowerDefinitions::ProjectileZ),
					Graphics::Colour::Yellow));
			lines.addVertex(
				Graphics::Vertex(
					System::Vector3f(
						(t.nextTile.x == -1 ? t.x : t.nextTile.x) * TowerDefinitions::TileSize + TowerDefinitions::TileSize / 2.0f,
						(t.nextTile.y == -1 ? t.y : t.nextTile.y) * TowerDefinitions::TileSize + TowerDefinitions::TileSize / 2.0f,
						TowerDefinitions::ProjectileZ),
					Graphics::Colour::Red));
		}

		lines.create();
		lines.render(_window, _renderData);
	}

	void Level::generateLevelPaths(void) {
		System::Vector2u startCoords;
		System::Vector2u endCoords;

		for (auto& t : m_Tiles) {
			if (t.type == Tile::Type::Start) {
				startCoords = System::Vector2u(t.x, t.y);
			}
			else if (t.type == Tile::Type::End) {
				endCoords = System::Vector2u(t.x, t.y);
			}
		}

		if (startCoords == endCoords) {
			throw std::runtime_error("Level has start and end coords the same.");
		}


		auto index = endCoords.y * width + endCoords.x;
		std::vector<Tile *> openTiles{ &m_Tiles[index] };
		openTiles[0]->nextTile = System::Vector2i(endCoords);

		while (openTiles.size() > 0) {
			Tile *t = openTiles[0];
			openTiles.erase(openTiles.begin());

			auto coords = System::Vector2u(t->x, t->y);

			if (t->x > 0) {
				// We can get the tile to the left
				auto& next = m_Tiles[(coords.y) * width + (coords.x - 1)];
				if (next.type != Tile::Type::NonPath && next.nextTile == System::Vector2i(-1, -1)) {
					next.nextTile = coords;
					openTiles.push_back(&next);
				}
			}
			if (t->y > 0) {
				// We can get the tile below
				auto& next = m_Tiles[(coords.y - 1) * width + (coords.x)];
				if (next.type != Tile::Type::NonPath && next.nextTile == System::Vector2i(-1, -1)) {
					next.nextTile = coords;
					openTiles.push_back(&next);
				}
			}
			if (t->x + 1 <= width) {
				// We can get the tile to the right
				auto& next = m_Tiles[(coords.y) * width + (coords.x + 1)];
				if (next.type != Tile::Type::NonPath && next.nextTile == System::Vector2i(-1, -1)) {
					next.nextTile = coords;
					openTiles.push_back(&next);
				}
			}
			if (t->y + 1 <= height) {
				// We can get the tile above
				auto& next = m_Tiles[(coords.y + 1) * width + (coords.x)];
				if (next.type != Tile::Type::NonPath && next.nextTile == System::Vector2i(-1, -1)) {
					next.nextTile = coords;
					openTiles.push_back(&next);
				}
			}
		}
	}

	void Level::reduceLivesRemaining(void) {
		reduceLivesRemaining(1);
	}
	void Level::reduceLivesRemaining(unsigned int _amount) {
		if (m_LivesRemaining <= _amount) {
			_amount = m_LivesRemaining;
		}
		m_LivesRemaining -= _amount;
		Infrastructure::InstanceCollection::getInstance<NotificationManager>().onLifeLost.invoke();
	}
	void Level::increaseLivesRemaining(void) {
		increaseLivesRemaining(1);
	}
	void Level::increaseLivesRemaining(unsigned int _amount) {
		m_LivesRemaining += _amount;
	}
	unsigned int Level::getLivesRemaining(void) const {
		return m_LivesRemaining;
	}

	Tile &Level::getTile(unsigned int _x, unsigned int _y) {
		return m_Tiles[_y * width + _x];
	}
}