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
			BuildRoom
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

		union {
			DigDirtJob			DigDirtData;
			BuildElevatorJob	BuildElevatorData;
			BuildRoomJob		BuildRoomData;
		};


		JobContextInfo() {
			JobType = None;
		}
		JobContextInfo(const DigDirtJob& _job) {
			DigDirtData = _job;
			JobType = DigDirt;
		}
		JobContextInfo(const BuildElevatorJob& _job) {
			BuildElevatorData = _job;
			JobType = BuildElevator;
		}
		JobContextInfo(const BuildRoomJob& _job) {
			BuildRoomData = _job;
			JobType = BuildRoom;
		}
	};
}

#endif // INCLUDED_DRILLER_MODELS_JOB_CONTEXT_INFO_HPP_