#ifndef INCLUDED_DRILLER_ELEMENTS_WORKER_ELEMENT_HPP_
#define INCLUDED_DRILLER_ELEMENTS_WORKER_ELEMENT_HPP_

#include <Driller/Elements/BaseElement.hpp>
#include <Driller/Elements/JobElement.hpp>

////////////////////////////////////////////////////////////
///
///	\namespace Driller
///
////////////////////////////////////////////////////////////
namespace Driller {
	////////////////////////////////////////////////////////////
	///
	///	\brief	Worker element for moving people things
	///
	////////////////////////////////////////////////////////////
	class WorkerElement : public BaseElement {
	public:
		////////////////////////////////////////////////////////////
		///
		///	\brief	Constructor
		///
		////////////////////////////////////////////////////////////
		WorkerElement(void);

		////////////////////////////////////////////////////////////
		///
		///	\brief	Updates the worker 
		///
		///	\param	The elapsed time for the update
		///
		////////////////////////////////////////////////////////////
		void update(float _delta) override;
		////////////////////////////////////////////////////////////
		///
		///	\brief	Handles an event for the worker
		///
		///	\param	The event to handle
		///
		///	\return	Whether the event was handled or not
		///
		////////////////////////////////////////////////////////////
		bool handleEvent(const System::Event& _event) override;
		////////////////////////////////////////////////////////////
		///
		///	\brief	Renders the worker
		///
		///	\param	The window to draw on
		///
		///	\param	The states to draw with
		///
		////////////////////////////////////////////////////////////
		void render(const Window::Window& _window, Graphics::RenderData _renderData) const override;

	private:
		////////////////////////////////////////////////////////////
		///
		///	\brief	Moves the worker towards the target
		///
		///	\param	The elapsed time for the update
		///
		////////////////////////////////////////////////////////////
		void moveTowardTarget(float _delta);

		////////////////////////////////////////////////////////////
		///
		///	\brief	Sets the workers job and target
		///
		///	\param	The new job
		///
		////////////////////////////////////////////////////////////
		void setJob(const JobElement& _job);

	private:
		unsigned int		m_VAO;						///<	OpenGL VAO handle
		unsigned int		m_VBO;						///<	OpenGL position VBO handle

		System::Vector2f	m_Position;					///<	Position of the worker
		System::Vector2f	m_TargetPosition;			///<	Target position of the worker

		JobElement			m_Job;						///<	The current job the worker has
	};
}

#endif // INCLUDED_DRILLER_ELEMENTS_WORKER_ELEMENT_HPP_