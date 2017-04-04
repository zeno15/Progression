#include <Driller/Managers/JobManager.hpp>

#include <Driller/Managers/NotificationService.hpp>

#include <Infrastructure/InstanceCollection.hpp>
#include <Infrastructure/SceneManager.hpp>

#include <Driller/DrillerDefinitions.hpp>
#include <Driller/Scenes/DrillerGameScene.hpp>

#include <algorithm>

namespace Driller {
	const std::string JobManager::Name = "JobManager";


	void JobManager::render(const Window::Window& _window, Graphics::RenderData _renderData) const {
		for (const auto& job : m_Jobs) {
			job->render(_window, _renderData);
		}
	}


	void JobManager::addJob(JobElement *_job) {
		m_Jobs.push_back(_job);
	}

	JobElement *JobManager::getJob(void) {
		if (jobExists()) {
			JobElement *job = m_Jobs.front();
			m_Jobs.erase(m_Jobs.begin());
			return job;
		}

		return nullptr;
	}

	bool JobManager::jobExists(void) {
		return m_Jobs.size() > 0;
	}

	JobElement *JobManager::getJob(std::function<bool(const JobElement *)> _predicate) {
		if (jobExists(_predicate)) {
			auto iterator = std::find_if(m_Jobs.begin(), m_Jobs.end(), _predicate);
			auto job = *iterator;
			m_Jobs.erase(iterator);
			return job;
		}

		return nullptr;
	}

	bool JobManager::jobExists(std::function<bool(const JobElement *)> _predicate) {
		return m_Jobs.end() != std::find_if(m_Jobs.begin(), m_Jobs.end(), _predicate);
	}

	JobElement *JobManager::peekJob(void) {
		if (jobExists()) {
			return m_Jobs.front();
		}

		return nullptr;
	}

	JobElement *JobManager::peekJob(std::function<bool(const JobElement *)> _predicate) {
		if (jobExists(_predicate)) {
			auto iterator = std::find_if(m_Jobs.begin(), m_Jobs.end(), _predicate);
			return *iterator;
		}

		return nullptr;
	}

	void JobManager::popJob(const JobElement *_job) {

		auto iterator = std::find_if(m_Jobs.begin(), m_Jobs.end(), [&](const JobElement *_j) {
			return 
				_j->m_JobInfo.JobType ==	_job->m_JobInfo.JobType &&
				_j->m_JobType ==			_job->m_JobType &&
				_j->m_TileCoordinates ==	_job->m_TileCoordinates &&
				_j->m_WorkPosition ==		_job->m_WorkPosition;
		});
		if (m_Jobs.end() != iterator) {
			m_Jobs.erase(iterator);
		}
	}
	JobElement *JobManager::getFirstAccessableJob(void) {
		auto& drillerGameScene = Infrastructure::InstanceCollection::getInstance<Infrastructure::SceneManager>().getScene<DrillerGameScene>("DrillerGameScene");

		for (auto& job : m_Jobs) {
			if (!job->isJobClaimed() && job->isAccessable(drillerGameScene)) {
				return job;
			}
		}

		return nullptr;
	}

	void JobManager::completeJob(JobElement *_job) {
		popJob(_job);
		_job->completeJob();
		delete _job;
	}
	void JobManager::cancelJob(JobElement *_job) {
		popJob(_job);
		Infrastructure::InstanceCollection::getInstance<NotificationService>().OnJobCancelled.invoke(_job);
		delete _job;
	}

	std::vector<JobElement *> JobManager::getJobsThatContainTile(const System::Vector2i& _tileCoordinates) {
		std::vector<JobElement *> jobs;

		for (auto& job : m_Jobs) {
			if (job->isTileContained(_tileCoordinates)) {
				jobs.push_back(job);
			}
		}

		return jobs;
	}
}