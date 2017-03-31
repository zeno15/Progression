#ifndef INCLUDED_DRILLER_MANAGERS_USER_INTERACTION_MANAGER_HPP_
#define INCLUDED_DRILLER_MANAGERS_USER_INTERACTION_MANAGER_HPP_

#include <Infrastructure/Manager.hpp>

#include <System/Vector2.hpp>

#include <Driller/DrillerDefinitions.hpp>

namespace System {
	class Event;
}

////////////////////////////////////////////////////////////
///
///	\namespace Driller
///
////////////////////////////////////////////////////////////
namespace Driller {
	////////////////////////////////////////////////////////////
	///
	///	\brief	Manager for handling user interactions
	///
	////////////////////////////////////////////////////////////
	class UserInteractionManager : public Infrastructure::Manager {
	public:
		friend class InstanceCollection;

		const static std::string Name;				///<	The name of the manager


		////////////////////////////////////////////////////////////
		///
		///	\brief	Constructor
		///
		////////////////////////////////////////////////////////////
		UserInteractionManager(void);

		////////////////////////////////////////////////////////////
		///
		///	\brief	Handles an event for the scene
		///
		///	\param	The event to handle
		///
		///	\return	Whether the event was handled or not
		///
		////////////////////////////////////////////////////////////
		bool handleEvent(const System::Event& _event);

		////////////////////////////////////////////////////////////
		///
		///	\brief	Converts from world to tile coordinates
		///
		///	\param	The world coordinates
		///
		///	\return	The tile coordinates
		///
		////////////////////////////////////////////////////////////
		static System::Vector2i getTilePositionFromWorldCoordinates(const System::Vector2f& _worldCoordinates);
		////////////////////////////////////////////////////////////
		///
		///	\brief	Converts from event to tile coordinates
		///
		///	\param	The event coordinates
		///
		///	\return	The tile coordinates
		///
		////////////////////////////////////////////////////////////
		static System::Vector2i getTilePositionFromEventCoordinates(const System::Vector2i& _eventCoordinates);
		////////////////////////////////////////////////////////////
		///
		///	\brief	Converts from event to world coordinates
		///
		///	\param	The event coordinates
		///
		///	\return	The world coordinates
		///
		////////////////////////////////////////////////////////////
		static System::Vector2f getWorldPositionFromEventCoordinates(const System::Vector2i& _eventCoordinates);

		////////////////////////////////////////////////////////////
		///
		///	\brief	Updates the current tile interaction context
		///
		///	\param	The new context
		///
		////////////////////////////////////////////////////////////
		void updateCurrentTileInteractionContext(DrillerDefinitions::TileInteractionContext _context);
		////////////////////////////////////////////////////////////
		///
		///	\brief	Gets the current tile interaction context
		///
		///	return The current context
		///
		////////////////////////////////////////////////////////////
		DrillerDefinitions::TileInteractionContext getCurrentTileInteractionContext(void) const;

	private:
		bool checkForActivatedTile(const System::Event& _event);

		DrillerDefinitions::TileInteractionContext m_CurrentTileInteractionContext;			///<	The context in which tile interactions are currently occuring
	};
}

#endif // INCLUDED_DRILLER_MANAGERS_USER_INTERACTION_MANAGER_HPP_