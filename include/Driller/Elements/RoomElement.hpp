#ifndef INCLUDED_DRILLER_ELEMENTS_ROOM_ELEMENT_HPP_
#define INCLUDED_DRILLER_ELEMENTS_ROOM_ELEMENT_HPP_

#include <Driller/Elements/BaseElement.hpp>

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

	private:
		void generateGraphics(void);

	private:
		unsigned int		m_VAO;						///<	OpenGL VAO handle
		unsigned int		m_VBO;						///<	OpenGL position VBO handle

		System::Vector2i	m_BottomLeft;				///<	The bottom left tile of the room
		System::Vector2i	m_SpriteSheetPosition;		///<	The bottom left of the sprite sheet
		System::Vector2u	m_RoomSize;					///<	The size of the room
	};
}

#endif // INCLUDED_DRILLER_ELEMENTS_ROOM_ELEMENT_HPP_