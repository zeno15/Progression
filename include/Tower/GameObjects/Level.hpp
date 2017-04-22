#ifndef INCLUDED_TOWER_GAME_OBJECTS_LEVEL_HPP_
#define INCLUDED_TOWER_GAME_OBJECTS_LEVEL_HPP_

#include <Tower/Components/Tile.hpp>

#include <Tower/GameObjects/GameObject.hpp>

#include <Graphics/VertexArray.hpp>

#include <vector>

namespace Tower {
	class Level : public GameObject {
	public:
		Level(void);
		Level(unsigned int _width, unsigned int _height);
		Level(unsigned int _width, unsigned int _height, std::vector<Tile>& _tiles);
		~Level(void);

		virtual void update(float _delta);
		virtual bool handleEvent(const System::Event& _event);
		virtual void render(const Window::Window& _window, Graphics::RenderData _renderData) const;

		void generateLevelPaths(void);

		void reduceLivesRemaining(void);
		void reduceLivesRemaining(unsigned int _amount);
		void increaseLivesRemaining(void);
		void increaseLivesRemaining(unsigned int _amount);
		unsigned int getLivesRemaining(void) const;

		const unsigned int width;
		const unsigned int height;

		Tile &getTile(unsigned int _x, unsigned int _y);

	private:
		unsigned int m_LivesRemaining;

		std::vector<Tile> m_Tiles;

		Graphics::VertexArray m_TileGraphics;
	};
}

#endif // INCLUDED_TOWER_GAME_OBJECTS_LEVEL_HPP_