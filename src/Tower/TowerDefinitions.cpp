#include <Tower/TowerDefinitions.hpp>

namespace Tower {
	const float TowerDefinitions::TileSize = 64.0f;

	const float TowerDefinitions::BackgroundZ = 0.0f;
	const float TowerDefinitions::CreepZ = 0.1f;
	const float TowerDefinitions::TowerZ = 0.1f;
	const float TowerDefinitions::ProjectileZ = 0.2f;
	const float TowerDefinitions::UIZ = 0.3f;
	const float TowerDefinitions::GhostZ = 0.4f;

	const Graphics::Colour TowerDefinitions::PathStartColour = Graphics::Colour::Red;
	const Graphics::Colour TowerDefinitions::PathEndColour = Graphics::Colour::Blue;
	const Graphics::Colour TowerDefinitions::PathColour = Graphics::Colour::Green;
}