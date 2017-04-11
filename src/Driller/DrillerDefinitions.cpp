#include <Driller/DrillerDefinitions.hpp>

namespace Driller {
	const std::string DrillerDefinitions::RelaseVersion = "Alpha";
	const std::string DrillerDefinitions::MajorVersion = "0";
	const std::string DrillerDefinitions::MinorVersion = "0";
	const std::string DrillerDefinitions::VersionString = RelaseVersion + " " + MajorVersion + "." + MinorVersion;

	const float DrillerDefinitions::TileWidth = 64.0f;
	const float DrillerDefinitions::TileHeight = 64.0f;

	const float DrillerDefinitions::BackgroundZ = 0.0f;
	const float DrillerDefinitions::BuildingZ = 0.1f;
	const float DrillerDefinitions::JobMarkerZ = 0.2f;
	const float DrillerDefinitions::EntityZ = 0.3f;

	const int DrillerDefinitions::MaximumWidth = 32;
	const int DrillerDefinitions::MaximumHeight = 16;

	const float DrillerDefinitions::ShuttleInterval = 30.0f; 
	const float DrillerDefinitions::MinimumShuttleLandingTime = 5.0f;
	const System::Vector2f DrillerDefinitions::ShuttleLandingPoint =	System::Vector2f(-DrillerDefinitions::TileWidth * 4.0f, 0.0f); 
	const System::Vector2f DrillerDefinitions::ShuttleBeginPoint =		System::Vector2f(-DrillerDefinitions::TileWidth * 16.0f, DrillerDefinitions::TileHeight * 12.0f);
	const System::Vector2f DrillerDefinitions::ShuttleEndPoint =		System::Vector2f(+DrillerDefinitions::TileWidth * 16.0f, DrillerDefinitions::TileHeight * 20.0f);

	const unsigned int DrillerDefinitions::BuildElevatorCost = 100;
	const unsigned int DrillerDefinitions::DigDirtCost = 20;
	const unsigned int DrillerDefinitions::MiningRoomCost = 100;
	const unsigned int DrillerDefinitions::DormRoomCost = 80;

	const System::Vector2i DrillerDefinitions::RoomData[RoomType::NumberRoomTypes][RoomInfo::NumberRoomInfo] = {
		// None
		{ System::Vector2i(0, 1), System::Vector2i(1, 1) },
		// Mining
		{ System::Vector2i(0, 4), System::Vector2i(3, 1) },
		// Dorm
		{ System::Vector2i(0, 3), System::Vector2i(2, 1) }
	};

}