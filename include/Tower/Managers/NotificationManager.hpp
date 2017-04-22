#ifndef INCLUDED_TOWER_MANAGERS_NOTIFICATION_MANAGER_HPP_
#define INCLUDED_TOWER_MANAGERS_NOTIFICATION_MANAGER_HPP_

#include <Infrastructure/Manager.hpp>

#include <Infrastructure/Signal.hpp>

namespace Tower {
	class Creep;
	class NotificationManager : public Infrastructure::Manager {
	public:
		friend class InstanceCollection;

		const static std::string Name;		///<	The name of the manager

		Infrastructure::Signal<Creep *> onCreepKilled;
		Infrastructure::Signal<Creep *> onCreepReachesEnd;
		Infrastructure::Signal<> onLifeLost;

	};
}

#endif // INCLUDED_TOWER_MANAGERS_NOTIFICATION_MANAGER_HPP_