#ifndef INCLUDED_DRILLER_MODELS_JOB_CONTEXT_INFO_HPP_
#define INCLUDED_DRILLER_MODELS_JOB_CONTEXT_INFO_HPP_

#include <Driller/DrillerDefinitions.hpp>

////////////////////////////////////////////////////////////
///
///	\namespace Driller
///
////////////////////////////////////////////////////////////
namespace Driller {
	////////////////////////////////////////////////////////////
	///
	///	\brief	Class to encapsulate all unique context info for jobs
	///
	////////////////////////////////////////////////////////////
	class JobContextInfo {
	public:

		enum {
			None,
			DigDirt,
			BuildElevator,
			BuildRoom,
			WorkRoom
		} JobType;

		struct DigDirtJob {
			DigDirtJob(int _column, int _level) :
				column(_column),
				level(_level) {
			}

			int column;
			int level;
		};

		struct BuildElevatorJob {
			BuildElevatorJob(int _level) :
				level(_level) {
			}

			int level;
		};

		struct BuildRoomJob {
			BuildRoomJob(int _column, int _level, DrillerDefinitions::RoomType _type) :
				column(_column),
				level(_level),
				type(_type) {
			}

			int column;
			int level;
			DrillerDefinitions::RoomType type;
		};

		struct WorkRoomJob {
			WorkRoomJob(int _column, int _level, DrillerDefinitions::RoomType _type, float _interval) :
				type(_type),
				column(_column),
				level(_level),
				interval(_interval) {
			}

			DrillerDefinitions::RoomType type;
			int column;
			int level;
			float interval;
		};

		int Priority;

		union {
			DigDirtJob			DigDirtData;
			BuildElevatorJob	BuildElevatorData;
			BuildRoomJob		BuildRoomData;
			WorkRoomJob			WorkRoomData;
		};

		////////////////////////////////////////////////////////////
		///
		///	\brief	Gets the tile size of the job
		///
		///	\return	The size
		///
		////////////////////////////////////////////////////////////
		System::Vector2i getJobTileSize(void) const {
			switch (JobType) {
			case BuildRoom:
				return DrillerDefinitions::RoomData[BuildRoomData.type][DrillerDefinitions::RoomInfo::SpriteSize];
			default:
				return System::Vector2i(1,1);
			}
		}

		////////////////////////////////////////////////////////////
		///
		///	\brief	Gets the interval for pseudo completing infinite jobs
		///
		///	\return The interval
		///
		////////////////////////////////////////////////////////////
		float getInfiniteInterval(void) const {
			switch (JobType) {
			case WorkRoom:
				return WorkRoomData.interval;
			default:
				return 0.0f;
			}
		}


		JobContextInfo() {
			JobType = None;
			Priority = 0;
		}
		JobContextInfo(const DigDirtJob& _job) {
			DigDirtData = _job;
			JobType = DigDirt;
			Priority = 40;
		}
		JobContextInfo(const BuildElevatorJob& _job) {
			BuildElevatorData = _job;
			JobType = BuildElevator;
			Priority = 100;
		}
		JobContextInfo(const BuildRoomJob& _job) {
			BuildRoomData = _job;
			JobType = BuildRoom;
			Priority = 50;
		}
		JobContextInfo(const WorkRoomJob& _job) {
			WorkRoomData = _job;
			JobType = WorkRoom;
			Priority = 10;
		}
		
		~JobContextInfo() {

		}
	};
}

#endif // INCLUDED_DRILLER_MODELS_JOB_CONTEXT_INFO_HPP_