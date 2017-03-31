#ifndef INCLUDED_DRILLER_MANAGERS_WORKER_MANAGER_HPP_
#define INCLUDED_DRILLER_MANAGERS_WORKER_MANAGER_HPP_

#include <Infrastructure/Manager.hpp>

#include <Driller/Elements/WorkerElement.hpp>

#include <vector>

////////////////////////////////////////////////////////////
///
///	\namespace Driller
///
////////////////////////////////////////////////////////////
namespace Driller {
	////////////////////////////////////////////////////////////
	///
	///	\brief	Manager for worker elements
	///
	////////////////////////////////////////////////////////////
	class WorkerManager : public Infrastructure::Manager {
	public:
		friend class InstanceCollection;

		const static std::string			Name;			///<	The name of the manager

		////////////////////////////////////////////////////////////
		///
		///	\brief	Updates the worker 
		///
		///	\param	The elapsed time for the update
		///
		////////////////////////////////////////////////////////////
		void update(float _delta);
		////////////////////////////////////////////////////////////
		///
		///	\brief	Handles an event for the worker
		///
		///	\param	The event to handle
		///
		///	\return	Whether the event was handled or not
		///
		////////////////////////////////////////////////////////////
		bool handleEvent(const System::Event& _event);
		////////////////////////////////////////////////////////////
		///
		///	\brief	Renders the worker
		///
		///	\param	The window to draw on
		///
		///	\param	The states to draw with
		///
		////////////////////////////////////////////////////////////
		void render(const Window::Window& _window, Graphics::RenderData _renderData) const;

		////////////////////////////////////////////////////////////
		///
		///	\brief	Adds a worker to the manager
		///
		///	\param	The worker to add
		///
		////////////////////////////////////////////////////////////
		void addWorker(WorkerElement *_worker);

	private:
		std::vector<WorkerElement *>		m_Workers;		///<	Vector of all worker elements
	};
}

#endif // INCLUDED_DRILLER_MANAGERS_WORKER_MANAGER_HPP_