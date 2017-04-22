#ifndef INCLUDED_TOWER_TOWER_DEFINITIONS_HPP_
#define INCLUDED_TOWER_TOWER_DEFINITIONS_HPP_

#include <System/Vector2.hpp>
#include <Graphics/Colour.hpp>

namespace Tower {
	class TowerDefinitions {
	public:
		static const float TileSize;

		static const float BackgroundZ;
		static const float CreepZ;
		static const float TowerZ;
		static const float ProjectileZ;
		static const float UIZ;
		static const float GhostZ;

		static const Graphics::Colour PathStartColour;
		static const Graphics::Colour PathEndColour;
		static const Graphics::Colour PathColour;
	};
}

#endif // INCLUDED_TOWER_TOWER_DEFINITIONS_HPP_