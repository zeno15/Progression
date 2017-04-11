#ifndef INCLUDED_DRILLER_DRILLER_DEFINITIONS_HPP_
#define INCLUDED_DRILLER_DRILLER_DEFINITIONS_HPP_

#include <string>

#include <System/Vector2.hpp>

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
		static const std::string RelaseVersion;					///<	The current dev release type
		static const std::string MajorVersion;					///<	The current major dev version
		static const std::string MinorVersion;					///<	The current minor dev version
		static const std::string VersionString;					///<	The current dev version

		static const float TileWidth;							///<	Width of a tile
		static const float TileHeight;							///<	Height of a tile

		static const float BackgroundZ;							///<	Z depth of background sprites
		static const float BuildingZ;							///<	Z depth of building sprites
		static const float EntityZ;								///<	Z depth of entity sprites
		static const float JobMarkerZ;							///<	Z depth of job markers
		

		static const int MaximumWidth;							///<	Maximum number of tiles away from elevator
		static const int MaximumHeight;							///<	Maximum number of tiles away from the surface

		static const float ShuttleInterval;						///<	The time between shuttle arrivals
		static const float MinimumShuttleLandingTime;			///<	The minimum time for the shuttle to land for
		static const System::Vector2f ShuttleLandingPoint;		///<	The coordinates of where the shuttle lands
		static const System::Vector2f ShuttleBeginPoint;		///<	The coordinates of where the shuttle begins
		static const System::Vector2f ShuttleEndPoint;			///<	The coordinates of where the shuttle ends

		static const unsigned int BuildElevatorCost;			///<	The cost of building an elevator
		static const unsigned int DigDirtCost;					///<	The cost of digging a dirt tile
		static const unsigned int MiningRoomCost;				///<	The cost of building a mining room
		static const unsigned int DormRoomCost;					///<	The cost of building a dorm room

		enum TileInteractionContext {
			NoContext,
			ResetContext,
			BuildRoomContext
		};

		enum JobType {
			Instant,
			Infinite,
			Time,
			Amount
		};

		enum RoomType {
			None,
			Mining,
			Dorm,
			NumberRoomTypes
		};
		enum RoomInfo {
			SpritePosition,
			SpriteSize,
			NumberRoomInfo
		};

		static const System::Vector2i RoomData[RoomType::NumberRoomTypes][RoomInfo::NumberRoomInfo];
	};
}

#endif // INCLUDED_DRILLER_DRILLER_DEFINITIONS_HPP_