#ifndef INCLUDED_DRILLER_MANAGERS_JOB_MANAGER_HPP_
#define INCLUDED_DRILLER_MANAGERS_JOB_MANAGER_HPP_

#include <vector>
#include <functional>

#include <Infrastructure/Manager.hpp>

#include <Driller/DrillerDefinitions.hpp>

#include <Driller/Elements/JobElement.hpp>

////////////////////////////////////////////////////////////
///
///	\namespace Driller
///
////////////////////////////////////////////////////////////
namespace Driller {
	////////////////////////////////////////////////////////////
	///
	///	\brief	Manager for jobs
	///
	////////////////////////////////////////////////////////////
	class JobManager : public Infrastructure::Manager {
	public:
		friend class InstanceCollection;

		const static std::string Name;				///<	The name of the manager


		////////////////////////////////////////////////////////////
		///
		///	\brief	Renders the scene
		///
		///	\param	The window to draw on
		///
		///	\param	The states to draw with
		///
		////////////////////////////////////////////////////////////
		void render(const Window::Window& _window, Graphics::RenderData _renderData) const;

		////////////////////////////////////////////////////////////
		///
		///	\brief	Adds a job to the queue
		///
		///	\param	_job	The job to add
		///
		////////////////////////////////////////////////////////////
		void addJob(JobElement _job);
		////////////////////////////////////////////////////////////
		///
		///	\brief	Gets a job off the queue
		///
		///	\return	Job from the queue
		///
		////////////////////////////////////////////////////////////
		JobElement getJob(void);
		////////////////////////////////////////////////////////////
		///
		///	\brief	Gets whether the queue has any jobs
		///
		///	\return	Whether the queue contains any jobs
		///
		////////////////////////////////////////////////////////////
		bool jobExists(void);
		////////////////////////////////////////////////////////////
		///
		///	\brief	Gets a job off the queue
		///
		///	\param	_predicate	The predicate to evaluate whether to return the job or not
		///
		///	\return	The first job that matches the given predicate
		///
		////////////////////////////////////////////////////////////
		JobElement getJob(std::function<bool(const JobElement& )> _predicate);
		////////////////////////////////////////////////////////////
		///
		///	\brief	Gets whether the queue has any jobs
		///
		///	\param	_predicate	The predicate to evaluate whether to return the job or not
		///
		///	\return	Whether there are any jobs that matche the given predicate
		///
		////////////////////////////////////////////////////////////
		bool jobExists(std::function<bool(const JobElement&)> _predicate);
		////////////////////////////////////////////////////////////
		///
		///	\brief	Gets a copy of a job off the queue
		///
		///	\return	Job from the queue
		///
		////////////////////////////////////////////////////////////
		JobElement peekJob(void);
		////////////////////////////////////////////////////////////
		///
		///	\brief	Gets a copy of a job off the queue 
		///
		///	\param	_predicate	The predicate to evaluate whether to return the job or not
		///
		///	\return	The first job that matches the given predicate
		///
		////////////////////////////////////////////////////////////
		JobElement peekJob(std::function<bool(const JobElement&)> _predicate);
		////////////////////////////////////////////////////////////
		///
		///	\brief	Pops the given peeked job off the queue
		///
		///	\param	Job from the queue
		///
		////////////////////////////////////////////////////////////
		void popJob(const JobElement& _job);

	private:
		std::vector<JobElement> m_Jobs;
	};
}

#endif // INCLUDED_DRILLER_MANAGERS_JOB_MANAGER_HPP_