#ifndef INCLUDED_PONG_MANAGERS_NOTIFICATION_MANAGER_HPP_
#define INCLUDED_PONG_MANAGERS_NOTIFICATION_MANAGER_HPP_

#include <Infrastructure/Manager.hpp>
#include <Infrastructure/Signal.hpp>

#include <Pong/PongDefinitions.hpp>

namespace Pong {
	class Ball;
}

////////////////////////////////////////////////////////////
///
///	\namespace Pong
///
////////////////////////////////////////////////////////////
namespace Pong {
	////////////////////////////////////////////////////////////
	///
	///	\brief	Manager for all game notifications
	///
	////////////////////////////////////////////////////////////
	class NotificationManager : public Infrastructure::Manager {
	public:
		friend class InstanceCollection;

		const static std::string Name;		///<	The name of the manager

		Infrastructure::Signal<const PongDefinitions::PaddleTeam&, Ball *> onBallLost;
	};
}

#endif // INCLUDED_PONG_MANAGERS_NOTIFICATION_MANAGER_HPP_