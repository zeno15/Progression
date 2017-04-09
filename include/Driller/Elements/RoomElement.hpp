#ifndef INCLUDED_DRILLER_ELEMENTS_ROOM_ELEMENT_HPP_
#define INCLUDED_DRILLER_ELEMENTS_ROOM_ELEMENT_HPP_

#include <Driller/Elements/BaseElement.hpp>

#include <Graphics/AnimatedSprite.hpp>

////////////////////////////////////////////////////////////
///
///	\namespace Driller
///
////////////////////////////////////////////////////////////
namespace Driller {

	////////////////////////////////////////////////////////////
	///
	///	\brief	Element representing a room
	///
	////////////////////////////////////////////////////////////
	class RoomElement : public BaseElement {
	public:
		////////////////////////////////////////////////////////////
		///
		///	\brief	Constructor
		///
		///	\param	The bottom left tile the room starts from
		///
		///	\param	The bottom left of the sprite in the sprite sheet
		///
		///	\param	The size of the room
		///
		////////////////////////////////////////////////////////////
		RoomElement(const System::Vector2i& _bottomLeftTile, const System::Vector2i& _spriteSheetPosition, const System::Vector2u& _roomSize);

		////////////////////////////////////////////////////////////
		///
		///	\brief	Updates the room 
		///
		///	\param	The elapsed time for the update
		///
		////////////////////////////////////////////////////////////
		virtual void update(float _delta) override;
		////////////////////////////////////////////////////////////
		///
		///	\brief	Handles an event for the room
		///
		///	\param	The event to handle
		///
		///	\return	Whether the event was handled or not
		///
		////////////////////////////////////////////////////////////
		virtual bool handleEvent(const System::Event& _event) override;
		////////////////////////////////////////////////////////////
		///
		///	\brief	Renders the room
		///
		///	\param	The window to draw on
		///
		///	\param	The states to draw with
		///
		////////////////////////////////////////////////////////////
		virtual void render(const Window::Window& _window, Graphics::RenderData _renderData) const override;

		////////////////////////////////////////////////////////////
		///
		///	\brief	Gets the bottom left tile of the room
		///
		///	\return	The bottom left tile
		///
		////////////////////////////////////////////////////////////
		const System::Vector2i& getBottomLeftTile(void) const;
		////////////////////////////////////////////////////////////
		///
		///	\brief	Gets the size of the room in tiles
		///
		///	\return	The size
		///
		////////////////////////////////////////////////////////////
		const System::Vector2i& getRoomSize(void) const;

		////////////////////////////////////////////////////////////
		///
		///	\brief	Method called when a room is created
		///
		////////////////////////////////////////////////////////////
		virtual void onRoomCreated(void) {}
		////////////////////////////////////////////////////////////
		///
		///	\brief	Method called when a room is removed
		///
		////////////////////////////////////////////////////////////
		virtual void onRoomRemoved(void) {}

	private:
		System::Vector2i	m_BottomLeft;				///<	The bottom left tile of the room
		System::Vector2i	m_SpriteSheetPosition;		///<	The bottom left of the sprite sheet
		System::Vector2u	m_RoomSize;					///<	The size of the room

		Graphics::AnimatedSprite		m_Graphics;		///<	The drawable room
	};
}

#endif // INCLUDED_DRILLER_ELEMENTS_ROOM_ELEMENT_HPP_