#ifndef INCLUDED_DRILLER_MANAGERS_ROOM_MANAGER_HPP_
#define INCLUDED_DRILLER_MANAGERS_ROOM_MANAGER_HPP_

#include <Driller/DrillerDefinitions.hpp>

#include <Driller/Elements/RoomElement.hpp>

#include <Infrastructure/Manager.hpp>

#include <Window/Window.hpp>

#include <Graphics/RenderData.hpp>

////////////////////////////////////////////////////////////
///
///	\namespace Driller
///
////////////////////////////////////////////////////////////
namespace Driller {
	////////////////////////////////////////////////////////////
	///
	///	\brief	Manager for rooms
	///
	////////////////////////////////////////////////////////////
	class RoomManager : public Infrastructure::Manager {
	public:
		friend class InstanceCollection;

		const static std::string Name;				///<	The name of the manager

		////////////////////////////////////////////////////////////
		///
		///	\brief	Constructor
		///
		////////////////////////////////////////////////////////////
		RoomManager(void);

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
		///	\brief	Handles an event for the manager
		///
		///	\param	The event to handle
		///
		///	\return	Whether the event was handled or not
		///
		////////////////////////////////////////////////////////////
		bool handleEvent(const System::Event& _event);
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
		///	\brief	Adds a room
		///
		///	\param	The room
		///
		////////////////////////////////////////////////////////////
		void addRoom(RoomElement *_room);
		////////////////////////////////////////////////////////////
		///
		///	\brief	Removes a room
		///
		///	\param	The room
		///
		////////////////////////////////////////////////////////////
		void removeRoom(RoomElement *_room);

		////////////////////////////////////////////////////////////
		///
		///	\brief	Gets the room that contains a given tile
		///
		///	\return	The room
		///
		////////////////////////////////////////////////////////////
		RoomElement *getRoomAtTile(const System::Vector2i& _tileCoordinates);

	private:
		void generateGhost(DrillerDefinitions::RoomType _roomType);
		void resetFromDrawingGhost(void);

	private:
		unsigned int		m_VAO;						///<	OpenGL VAO handle
		unsigned int		m_VBO;						///<	OpenGL position VBO handle

		bool				m_DrawingGhost;				///<	Whether the ghost is being drawn
		bool				m_IsCurrentPositionValid;	///<	Whether the position of the ghost is valid
		DrillerDefinitions::RoomType m_CurrentRoom;		///<	The currentRoomTypeToBeDrawn

		System::Vector2i	m_BottomLeftTile;			///<	The bottom left tile to draw the ghost from
		System::Vector2u	m_CurrentGhostSize;			///<	The size of the current ghost

		std::vector<RoomElement *> m_Rooms;				///<	Collection of rooms
	};
}

#endif // INCLUDED_DRILLER_MANAGERS_ROOM_MANAGER_HPP_