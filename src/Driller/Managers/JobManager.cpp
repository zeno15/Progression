#include <Driller/Managers/JobManager.hpp>

#include <Driller/Managers/NotificationService.hpp>

#include <Driller/Elements/WorkerElement.hpp>

#include <Infrastructure/InstanceCollection.hpp>
#include <Infrastructure/SceneManager.hpp>

#include <Driller/DrillerDefinitions.hpp>
#include <Driller/Scenes/DrillerGameScene.hpp>

#include <algorithm>
#include <iostream>

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
		if (_job->getJobType() != DrillerDefinitions::JobType::Infinite) {
			popJob(_job);
			_job->completeJob();
			delete _job;
		}
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
	
	void JobManager::registerWorkerForJob(WorkerElement *_worker) {
		m_WorkersLookingForJobs.push_back(_worker);
	}

	void JobManager::assignWorkersJobs(void) {
		if (m_WorkersLookingForJobs.size() <= 0) {
			return;
		}
		auto& drillerGameScene = Infrastructure::InstanceCollection::getInstance<Infrastructure::SceneManager>().getScene<DrillerGameScene>("DrillerGameScene");

		std::vector<JobElement *> unclaimedJobs;

		for (auto job : m_Jobs) {
			if (!job->isJobClaimed()) {
				unclaimedJobs.push_back(job);
			}
		}

		if (unclaimedJobs.size() == 0) {
			m_WorkersLookingForJobs.clear();
			return;
		}

		std::sort(unclaimedJobs.begin(), unclaimedJobs.end(), [](JobElement *lhs, JobElement *rhs) {
			return lhs->getJobInfo().Priority > rhs->getJobInfo().Priority;
		});
		std::cout << "There are " << m_WorkersLookingForJobs.size() << " worker(s) looking for work and " << unclaimedJobs.size() << " unclaimed jobs" << std::endl;

		std::vector<std::vector<std::pair<WorkerElement *, unsigned int >>> workerJobsScores;

		for (unsigned int iJob = 0; iJob < unclaimedJobs.size(); iJob += 1) {
			workerJobsScores.push_back(std::vector<std::pair<WorkerElement *, unsigned int>>());

			for (unsigned int iWorker = 0; iWorker < m_WorkersLookingForJobs.size(); iWorker += 1) {

				unsigned int priorityScore = unclaimedJobs[iJob]->getJobInfo().Priority;
				unsigned int distanceScore = createDistanceScore(unclaimedJobs[iJob]->getTileCoordinates(), m_WorkersLookingForJobs[iWorker]->getTilePosition());
				unsigned int score = priorityScore + distanceScore;

				if (!unclaimedJobs[iJob]->isAccessable(drillerGameScene)) {
					score = std::numeric_limits<unsigned int>::max();
				}

				auto result = std::pair<WorkerElement *, unsigned int>(
					m_WorkersLookingForJobs[iWorker],
					score);


				workerJobsScores[iJob].push_back(result);
			}
		}


		for (unsigned int iJob = 0; iJob < unclaimedJobs.size(); iJob += 1) {
			auto job = unclaimedJobs[iJob];
			auto bestScore = std::numeric_limits<unsigned int>::max();
			auto bestScoreIndex = 0;
			for (unsigned int iWorker = 0; iWorker < m_WorkersLookingForJobs.size(); iWorker += 1) {
				if (m_WorkersLookingForJobs[iWorker]->getJob() == nullptr) {
					if (bestScore > workerJobsScores[iJob][iWorker].second) {
						bestScore = workerJobsScores[iJob][iWorker].second;
						bestScoreIndex = iWorker;
					}
				}
			}

			if (bestScore != std::numeric_limits<unsigned int>::max()) {
				m_WorkersLookingForJobs[bestScoreIndex]->setJob(job);
			}
		}


		m_WorkersLookingForJobs.clear();
	}

	unsigned int JobManager::createDistanceScore(const System::Vector2i& _jobCoordinates, const System::Vector2i& _tileCoordinates) {
		if (_jobCoordinates.y == _tileCoordinates.y) {
			return static_cast<unsigned int>(std::abs(_jobCoordinates.x) + std::abs(_tileCoordinates.x));
		}

		int jobDistance = std::abs(static_cast<int>(_jobCoordinates.x));
		int tileDistance = std::abs(static_cast<int>(_tileCoordinates.x));
		int elevatorDistance = static_cast<unsigned int>(std::abs(_jobCoordinates.y) - std::abs(_tileCoordinates.y));

		return static_cast<unsigned int>(jobDistance + tileDistance + elevatorDistance);
	}
}