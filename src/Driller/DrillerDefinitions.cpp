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
}