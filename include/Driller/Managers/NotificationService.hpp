#ifndef INCLUDED_DRILLER_MANAGERS_NOTIFICATION_SERVICE_HPP_
#define INCLUDED_DRILLER_MANAGERS_NOTIFICATION_SERVICE_HPP_

#include <string>

#include <Infrastructure/Manager.hpp>
#include <Infrastructure/Signal.hpp>

#include <Driller/DrillerDefinitions.hpp>

////////////////////////////////////////////////////////////
///
///	\namespace Driller
///
////////////////////////////////////////////////////////////
namespace Driller {
	////////////////////////////////////////////////////////////
	///
	///	\brief	Notification service for game events
	///
	////////////////////////////////////////////////////////////
	class NotificationService : public Infrastructure::Manager {
	public:
		friend class InstanceCollection;

		const static std::string Name;																				///<	The name of the manager

	public:
		Infrastructure::Signal<int, int, DrillerDefinitions::TileInteractionContext> OnTileActivated;				///<	Occurs when a tile is activated
	};
}

#endif // INCLUDED_DRILLER_MANAGERS_NOTIFICATION_SERVICE_HPP_