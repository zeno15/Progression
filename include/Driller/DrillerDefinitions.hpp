#ifndef INCLUDED_DRILLER_DRILLER_DEFINITIONS_HPP_
#define INCLUDED_DRILLER_DRILLER_DEFINITIONS_HPP_

#include <string>

////////////////////////////////////////////////////////////
///
///	\namespace Driller
///
////////////////////////////////////////////////////////////
namespace Driller {
	////////////////////////////////////////////////////////////
	///
	///	\brief	Common definitions for Driller
	///
	////////////////////////////////////////////////////////////
	class DrillerDefinitions {
	public:
		static const std::string RelaseVersion;			///<	The current dev release type
		static const std::string MajorVersion;			///<	The current major dev version
		static const std::string MinorVersion;			///<	The current minor dev version
		static const std::string VersionString;			///<	The current dev version

		static const float TileWidth;					///<	Width of a tile
		static const float TileHeight;					///<	Height of a tile

		static const int MaximumWidth;					///<	Maximum number of tiles away from elevator
		static const int MaximumHeight;					///<	Maximum number of tiles away from the surface

		enum TileInteractionContext {
			NoContext,
			BuildRoomContext
		};

		enum JobType {
			Instant,
			Infinite,
			Time,
			Amount
		};
	};
}

#endif // INCLUDED_DRILLER_DRILLER_DEFINITIONS_HPP_