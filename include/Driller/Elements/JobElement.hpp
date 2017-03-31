#ifndef INCLUDED_DRILLER_ELEMENTS_JOB_ELEMENT_HPP_
#define INCLUDED_DRILLER_ELEMENTS_JOB_ELEMENT_HPP_

#include <Driller/DrillerDefinitions.hpp>
#include <Driller/Elements/BaseElement.hpp>

#include <Infrastructure/Signal.hpp>

namespace Driller {
	class DrillerGameScene;
}

////////////////////////////////////////////////////////////
///
///	\namespace Driller
///
////////////////////////////////////////////////////////////
namespace Driller {
	////////////////////////////////////////////////////////////
	///
	///	\brief	Element representing a workable job
	///
	////////////////////////////////////////////////////////////
	class JobElement : public BaseElement {
	public:
		////////////////////////////////////////////////////////////
		///
		///	\brief	Constructor
		///
		///	\param	_jobName				The job name
		///
		////////////////////////////////////////////////////////////
		JobElement(const std::string& _jobName);
		////////////////////////////////////////////////////////////
		///
		///	\brief	Constructor
		///
		///	\param	_jobName				The job name
		///
		///	\param	_tileCoordinates		The tile coordinates for the job
		///
		////////////////////////////////////////////////////////////
		JobElement(const std::string& _jobName, const System::Vector2i& _tileCoordinates);
		////////////////////////////////////////////////////////////
		///
		///	\brief	Constructor
		///
		///	\param	_jobName				The job name
		///
		///	\param	_tileCoordinates		The tile coordinates for the job
		///
		///	\param	_workPosition			The absolute coordinates to work the job at
		///
		////////////////////////////////////////////////////////////
		JobElement(const std::string& _jobName, const System::Vector2i& _tileCoordinates, const System::Vector2f& _workPosition);
		////////////////////////////////////////////////////////////
		///
		///	\brief	Constructor
		///
		///	\param	_jobName				The job name
		///
		///	\param	_tileCoordinates		The tile coordinates for the job
		///
		///	\param	_workPosition			The absolute coordinates to work the job at
		///
		///	\param	_jobType				The type of job
		///
		////////////////////////////////////////////////////////////
		JobElement(const std::string& _jobName, const System::Vector2i& _tileCoordinates, const System::Vector2f& _workPosition, DrillerDefinitions::JobType _jobType);


		////////////////////////////////////////////////////////////
		///
		///	\brief	Destructor
		///
		////////////////////////////////////////////////////////////
		~JobElement(void);

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
		///	\brief	Performs work on the job
		///
		///	\param	The length of time worked
		///
		///	\return	Whether the jon was completed
		///
		////////////////////////////////////////////////////////////
		bool workTimedJob(float _delta);

		////////////////////////////////////////////////////////////
		///
		///	\brief	Gets the job name
		///
		///	\return	The job name
		///
		////////////////////////////////////////////////////////////
		std::string getJobName(void) const;
		////////////////////////////////////////////////////////////
		///
		///	\brief	Gets the tile coordinates
		///
		///	\return	The tile coordinates
		///
		////////////////////////////////////////////////////////////
		System::Vector2i getTileCoordinates(void) const;
		////////////////////////////////////////////////////////////
		///
		///	\brief	Gets the absolute work position
		///
		///	\return	The absolute work position
		///
		////////////////////////////////////////////////////////////
		System::Vector2f getWorkPosition(void) const;
		////////////////////////////////////////////////////////////
		///
		///	\brief	Gets the job type
		///
		///	\return	The job type
		///
		////////////////////////////////////////////////////////////
		DrillerDefinitions::JobType getJobType(void) const;

		////////////////////////////////////////////////////////////
		///
		///	\brief	Sets the remaining time 
		///
		///	\param	_remainingTime	The remaining time until the job is complete
		///
		////////////////////////////////////////////////////////////
		void setRemaingTime(float _remainingTime);
		////////////////////////////////////////////////////////////
		///
		///	\brief	Reduces the remaining time
		///
		///	\param	_reduction		The reduction in time until the job is complete
		///
		////////////////////////////////////////////////////////////
		void reduceRemainingTime(float _reduction);
		////////////////////////////////////////////////////////////
		///
		///	\brief	Gets the remaining time
		///
		///	\return	The time remaining until the job is complete
		///
		////////////////////////////////////////////////////////////
		float getRemainingTime(void) const;

		////////////////////////////////////////////////////////////
		///
		///	\brief	Sets the remaining work 
		///
		///	\param	_remainingWork	The remaining work until the job is complete
		///
		////////////////////////////////////////////////////////////
		void setRemainingAmount(unsigned int _remainingAmount);
		////////////////////////////////////////////////////////////
		///
		///	\brief	Reduces the remaining work
		///
		///	\param	_reduction		The reduction in work until the job is complete
		///
		////////////////////////////////////////////////////////////
		void reduceRemainingAmount(unsigned int _reduction);
		////////////////////////////////////////////////////////////
		///
		///	\brief	Gets the remaining work
		///
		///	\return	The work remaining until the job is complete
		///
		////////////////////////////////////////////////////////////
		unsigned int getRemainingAmount(void) const;

		////////////////////////////////////////////////////////////
		///
		///	\brief	Completes the job
		///
		////////////////////////////////////////////////////////////
		void completeJob(void);

		////////////////////////////////////////////////////////////
		///
		///	\brief	Gets whether the tile is accessible
		///
		///	\param	The game scene
		///
		///	\return	Whether the tile is accessible
		///
		////////////////////////////////////////////////////////////
		bool isAccessable(DrillerGameScene& _scene) const;

		Infrastructure::Signal<const JobElement&>	onJobComplete;

		std::string							m_JobName;					///<	The job name
		System::Vector2i					m_TileCoordinates;			///<	The tile coordinates for the job
		System::Vector2f					m_WorkPosition;				///<	The absolute coordinates to work the job at
		DrillerDefinitions::JobType			m_JobType;					///<	The type of job

		float								m_RemainingTime;			///<	Remaining time until job is complete
		unsigned int						m_RemainingAmount;			///<	Remaining work until job is complete

		unsigned int						m_VAO;						///<	OpenGL VAO handle
		unsigned int						m_VBO;						///<	OpenGL position VBO handle
	};
}

#endif // INCLUDED_DRILLER_ELEMENTS_JOB_ELEMENT_HPP_