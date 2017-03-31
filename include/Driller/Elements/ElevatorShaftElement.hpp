#ifndef INCLUDED_DRILLER_ELEMENTS_ELEVATOR_SHAFT_ELEMENT_HPP_
#define INCLUDED_DRILLER_ELEMENTS_ELEVATOR_SHAFT_ELEMENT_HPP_

#include <Driller/Elements/BaseElement.hpp>

////////////////////////////////////////////////////////////
///
///	\namespace Driller
///
////////////////////////////////////////////////////////////
namespace Driller {
	////////////////////////////////////////////////////////////
	///
	///	\brief	Element that comprises a individual elevator shaft tile
	///
	////////////////////////////////////////////////////////////
	class ElevatorShaftElement : public BaseElement {
	public:
		////////////////////////////////////////////////////////////
		///
		///	\brief	Constructor
		///	
		///	\param	The level of the elevator shaft
		///
		////////////////////////////////////////////////////////////
		ElevatorShaftElement(unsigned int _level);
		////////////////////////////////////////////////////////////
		///
		///	\brief	Destructor
		///	
		////////////////////////////////////////////////////////////
		~ElevatorShaftElement(void);


		////////////////////////////////////////////////////////////
		///
		///	\brief	Updates the element 
		///
		///	\param	The elapsed time for the update
		///
		////////////////////////////////////////////////////////////
		void update(float _delta) override;
		////////////////////////////////////////////////////////////
		///
		///	\brief	Handles an event for the element
		///
		///	\param	The event to handle
		///
		///	\return	Whether the event was handled or not
		///
		////////////////////////////////////////////////////////////
		bool handleEvent(const System::Event& _event) override;
		////////////////////////////////////////////////////////////
		///
		///	\brief	Renders the element
		///
		///	\param	The window to draw on
		///
		///	\param	The states to draw with
		///
		////////////////////////////////////////////////////////////
		void render(const Window::Window& _window, Graphics::RenderData _renderData) const override;

		////////////////////////////////////////////////////////////
		///
		///	\brief	Gets whether the elevator has been built or not
		///
		///	\return	Whether the elevator is built
		///
		////////////////////////////////////////////////////////////
		bool isBuilt(void) const;
		////////////////////////////////////////////////////////////
		///
		///	\brief	Sets whether the elevator is built
		///
		///	\param	Whether the elevator is built
		///
		////////////////////////////////////////////////////////////
		void setIsBuilt(bool _isBuilt);

		////////////////////////////////////////////////////////////
		///
		///	\brief	sets whether the tile is clear or not
		///
		///	\param	Whether the tile has a jon queued
		///
		////////////////////////////////////////////////////////////
		void setJobQueuedFlag(bool _flag);
		////////////////////////////////////////////////////////////
		///
		///	\brief	Gets whether the tile has a job queued
		///
		///	\return	Whether the tile has a job queued
		///
		////////////////////////////////////////////////////////////
		bool getJobQueued(void) const;

	private:
		unsigned int		m_Level;					///<	The number of levels below the ground
		unsigned int		m_VAO;						///<	OpenGL VAO handle
		unsigned int		m_VBO;						///<	OpenGL position VBO handle

		bool				m_IsBuilt;					///<	Whether the elevator is built
		bool				m_HasJobQueued;				///<	Whether the elevator has a job queued on it or not
	};
}

#endif // INCLUDED_DRILLER_ELEMENTS_ELEVATOR_SHAFT_ELEMENT_HPP_