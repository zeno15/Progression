#include <Driller/Managers/WorkerManager.hpp>

#include <Driller/Managers/JobManager.hpp>

#include <Infrastructure/InstanceCollection.hpp>


namespace Driller {
	const std::string WorkerManager::Name = "WorkerManager"; 
	
	
	void WorkerManager::update(float _delta) {
		for (auto& worker : m_Workers) {
			worker->update(_delta);
		}

		Infrastructure::InstanceCollection::getInstance<JobManager>().assignWorkersJobs();
	}

	bool WorkerManager::handleEvent(const System::Event& _event) {
		for (auto& worker : m_Workers) {
			if (worker->handleEvent(_event)) {
				return true;
			}
		}
		return false;
	}

	void WorkerManager::render(const Window::Window& _window, Graphics::RenderData _renderData) const {
		for (auto& worker : m_Workers) {
			worker->render(_window, _renderData);
		}
	}

	void WorkerManager::addWorker(WorkerElement *_worker) {
		m_Workers.push_back(_worker);
	}

	void WorkerManager::onJobCancelled(JobElement *_job) {
		for (auto& worker : m_Workers) {
			if (worker->getJob() == _job) {
				worker->setJob(nullptr);
			}
		}
	}
}