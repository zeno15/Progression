#ifndef INCLUDED_TOWER_COMPONENTS_TILE_HPP_
#define INCLUDED_TOWER_COMPONENTS_TILE_HPP_

#include <Graphics/Colour.hpp>

#include <System/Vector2.hpp>

namespace Tower {
	class TowerBase;

	class Tile {
	public:
		Tile(unsigned int _x, unsigned int _y);

		enum Type {
			Path,
			NonPath,
			Start,
			End
		};

		Graphics::Colour getBaseColourForTile(void) const;

		bool canTowerBeBuilt(void) const;

		const unsigned int x;
		const unsigned int y;

		TowerBase *m_Tower;

		System::Vector2i nextTile;

		Type type;
	};
}

#endif // INCLUDED_TOWER_COMPONENTS_TILE_HPP_