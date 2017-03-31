#include <Driller/Managers/JobManager.hpp>

#include <algorithm>

namespace Driller {
	const std::string JobManager::Name = "JobManager";


	void JobManager::render(const Window::Window& _window, Graphics::RenderData _renderData) const {
		for (const auto& job : m_Jobs) {
			job.render(_window, _renderData);
		}
	}


	void JobManager::addJob(JobElement _job) {
		m_Jobs.push_back(_job);
	}

	JobElement JobManager::getJob(void) {
		if (jobExists()) {
			JobElement job = JobElement(m_Jobs.front());
			m_Jobs.erase(m_Jobs.begin());
			return job;
		}

		return JobElement("");
	}

	bool JobManager::jobExists(void) {
		return m_Jobs.size() > 0;
	}

	JobElement JobManager::getJob(std::function<bool(const JobElement&)> _predicate) {
		if (jobExists(_predicate)) {
			auto iterator = std::find_if(m_Jobs.begin(), m_Jobs.end(), _predicate);
			auto job = JobElement(*iterator);
			m_Jobs.erase(iterator);
			return job;
		}

		return JobElement("");
	}

	bool JobManager::jobExists(std::function<bool(const JobElement&)> _predicate) {
		return m_Jobs.end() != std::find_if(m_Jobs.begin(), m_Jobs.end(), _predicate);
	}

	JobElement JobManager::peekJob(void) {
		if (jobExists()) {
			return m_Jobs.front();
		}

		return JobElement("");
	}

	JobElement JobManager::peekJob(std::function<bool(const JobElement&)> _predicate) {
		if (jobExists(_predicate)) {
			auto iterator = std::find_if(m_Jobs.begin(), m_Jobs.end(), _predicate);
			return JobElement(*iterator);
		}

		return JobElement("");
	}

	void JobManager::popJob(const JobElement& _job) {

		auto iterator = std::find_if(m_Jobs.begin(), m_Jobs.end(), [&](const JobElement& _j) {
			return 
				_j.m_JobName == _job.m_JobName &&
				_j.m_JobType == _job.m_JobType &&
				_j.m_TileCoordinates == _job.m_TileCoordinates &&
				_j.m_WorkPosition == _job.m_WorkPosition;
		});
		if (m_Jobs.end() != iterator) {
			m_Jobs.erase(iterator);
		}
	}
}