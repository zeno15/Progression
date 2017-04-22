#include <Tower/Components/Tile.hpp>

#include <Tower/GameObjects/TowerBase.hpp>

namespace Tower {

	Tile::Tile(unsigned int _x, unsigned int _y) :
		x(_x),
		y(_y),
		type(NonPath),
		nextTile(-1, -1),
		m_Tower(nullptr) {

	}

	Graphics::Colour Tile::getBaseColourForTile(void) const {
		switch (type) {
		case Path:
			return Graphics::Colour::Green;
		case Start:
			return Graphics::Colour::Red;
		case End:
			return Graphics::Colour::Blue;
		default:
			return Graphics::Colour::Cyan;
		}
	}
	bool Tile::canTowerBeBuilt(void) const {
		return type == NonPath && m_Tower == nullptr;
	}
}