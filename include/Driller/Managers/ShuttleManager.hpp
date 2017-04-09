#ifndef INCLUDED_DRILLER_MANAGERS_SHUTTLE_MANAGER_HPP_
#define INCLUDED_DRILLER_MANAGERS_SHUTTLE_MANAGER_HPP_

#include <Infrastructure/Manager.hpp>

#include <Driller/Elements/ShuttleElement.hpp>

////////////////////////////////////////////////////////////
///
///	\namespace Driller
///
////////////////////////////////////////////////////////////
namespace Driller {
	////////////////////////////////////////////////////////////
	///
	///	\brief	Manager for the shuttle
	///
	////////////////////////////////////////////////////////////
	class ShuttleManager : public Infrastructure::Manager {
	public:
		friend class InstanceCollection;

		const static std::string Name;				///<	The name of the manager

		////////////////////////////////////////////////////////////
		///
		///	\brief	Constructor
		///
		////////////////////////////////////////////////////////////
		ShuttleManager(void);

		////////////////////////////////////////////////////////////
		///
		///	\brief	Updates the manager 
		///
		///	\param	The elapsed time for the update
		///
		////////////////////////////////////////////////////////////
		void update(float _delta);
		////////////////////////////////////////////////////////////
		///
		///	\brief	Renders the manager
		///
		///	\param	The window to draw on
		///
		///	\param	The states to draw with
		///
		////////////////////////////////////////////////////////////
		void render(const Window::Window& _window, Graphics::RenderData _renderData) const;

		////////////////////////////////////////////////////////////
		///
		///	\brief	Creates the shuttle
		///
		////////////////////////////////////////////////////////////
		void createShuttle(void);

	private:
		float			m_TimeToShuttleArrival;				///<	The time until the shuttle next arrives
		bool			m_IsShuttleInTransit;				///<	Whether the shuttle is in transit

		ShuttleElement	*m_Shuttle;							///<	The shuttle
	};

}

#endif // INCLUDED_DRILLER_MANAGERS_SHUTTLE_MANAGER_HPP_