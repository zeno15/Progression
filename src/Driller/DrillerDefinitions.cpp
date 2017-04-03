#include <Driller/DrillerDefinitions.hpp>

namespace Driller {
	const std::string DrillerDefinitions::RelaseVersion = "Alpha";
	const std::string DrillerDefinitions::MajorVersion = "0";
	const std::string DrillerDefinitions::MinorVersion = "0";
	const std::string DrillerDefinitions::VersionString = RelaseVersion + " " + MajorVersion + "." + MinorVersion;

	const float DrillerDefinitions::TileWidth = 64.0f;
	const float DrillerDefinitions::TileHeight = 64.0f;

	const int DrillerDefinitions::MaximumWidth = 32;
	const int DrillerDefinitions::MaximumHeight = 16;


	const System::Vector2i DrillerDefinitions::RoomData[RoomType::NumberRoomTypes][RoomInfo::NumberRoomInfo] = {
		// None
		{ System::Vector2i(0, 1), System::Vector2i(1, 1) },
		// Mining
		{ System::Vector2i(0, 4), System::Vector2i(3, 1) },
		// Dorm
		{ System::Vector2i(0, 3), System::Vector2i(2, 1) }
	};

}