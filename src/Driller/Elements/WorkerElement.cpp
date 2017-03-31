#include <Driller/Elements/WorkerElement.hpp>

#include <Infrastructure/InstanceCollection.hpp>
#include <Infrastructure/ShaderManager.hpp>
#include <Infrastructure/TextureManager.hpp>
#include <Infrastructure/SceneManager.hpp>

#include <Driller/DrillerDefinitions.hpp>
#include <Driller/DrillerResources.hpp>
#include <Driller/Elements/ElementHelpers.hpp>
#include <Driller/Managers/JobManager.hpp>
#include <Driller/Scenes/DrillerGameScene.hpp>

#include <Window/OpenGL.hpp>

#include <iostream>

#define SPEED_X 2.0f * DrillerDefinitions::TileWidth
#define SPEED_Y 2.0f * DrillerDefinitions::TileHeight

namespace Driller {

	WorkerElement::WorkerElement(void) :
	m_Job(""),
	m_VAO(0),
	m_VBO(0) {
		ElementHelpers::createBasicDoubleTriQuadForTextureId(DrillerResources::WorkerSpriteIndex, &m_VAO, &m_VBO);

		m_Position = System::Vector2f(DrillerDefinitions::TileWidth * -8.0f, DrillerDefinitions::TileHeight * -1.0f);
		m_TargetPosition = m_Position;
	}


	void WorkerElement::update(float _delta) {
		if (m_TargetPosition != m_Position) {
			moveTowardTarget(_delta);
		}
		else {
			if (m_Job.getJobName() == "") {
				// We don't have a job so lets try find one
				auto& jobManager = Infrastructure::InstanceCollection::getInstance<JobManager>();
				auto& drillerGameScene = Infrastructure::InstanceCollection::getInstance<Infrastructure::SceneManager>().getScene<DrillerGameScene>("DrillerGameScene");

				if (jobManager.jobExists([&](const JobElement& _job) {
					return _job.getJobName() == "DigDirt" && _job.isAccessable(drillerGameScene);
				})) {
					auto job = jobManager.peekJob([&](const JobElement& _job) {
						return _job.getJobName() == "DigDirt" && _job.isAccessable(drillerGameScene);
					});


					jobManager.popJob(job);
					setJob(job);
				}

				if (jobManager.jobExists([](const JobElement& _job) {
					return _job.getJobName() == "BuildElevator";
				})) {
					auto job = jobManager.peekJob([](const JobElement& _job) {
						return _job.getJobName() == "BuildElevator";
					});


					jobManager.popJob(job);
					setJob(job);
				}

				if (jobManager.jobExists([](const JobElement& _job) {
					return _job.getJobName() == "Build";
				})) {
					auto job = jobManager.peekJob([](const JobElement& _job) {
						return _job.getJobName() == "Build";
					});

					jobManager.popJob(job);
					setJob(job);
				}
			}
			else {
				// We have a job and we are at our target
				if (m_Job.workTimedJob(_delta)) {
					m_Job.completeJob();
				}
			}
		}
	}
	bool WorkerElement::handleEvent(const System::Event& _event) {
		return false;
	}
	void WorkerElement::render(const Window::Window& _window, Graphics::RenderData _renderData) const {
		auto& shader = Infrastructure::InstanceCollection::getInstance<Infrastructure::ShaderManager>().getShader(DrillerResources::StaticTexturedShaderName);
		shader.bind();
		shader.passUniform(DrillerResources::StaticTexturedShaderMVPUniformName, _renderData.projection * _renderData.view * System::Mat4x4::createTranslation(System::Vector3f(m_Position.x, -m_Position.y, 0.3f)));
		Infrastructure::InstanceCollection::getInstance<Infrastructure::TextureManager>().getTexture(DrillerResources::SpriteSheetName).bind();
		glBindVertexArray(m_VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		if (m_Job.getJobName() != "") {
			m_Job.render(_window, _renderData);
		}
	}

	void WorkerElement::moveTowardTarget(float _delta) {
		bool isOnCorrectLevel = m_TargetPosition.y == m_Position.y;
		if (!isOnCorrectLevel) {
			if (m_Position.x != 0.0f) {
				float xDirection = m_Position.x > 0 ? -1.0f : +1.0f;

				float distance = SPEED_X * _delta;

				if (std::abs(m_Position.x) <= distance) {
					m_Position.x = 0.0f;
				}
				else {
					m_Position.x += distance * xDirection;
				}
			}
			else {
				float yDirection = m_Position.y < m_TargetPosition.y ? +1.0f : -1.0f;

				float distance = SPEED_Y * _delta;

				float remaining = std::fabsf(m_TargetPosition.y - m_Position.y);

				if (remaining <= distance) {
					m_Position.y = m_TargetPosition.y;
				}
				else {
					m_Position.y += distance * yDirection;
				}
			}
		}
		else {
			float xDirection = m_Position.x > m_TargetPosition.x ? -1.0f : +1.0f;

			float distance = SPEED_X * _delta;

			if (std::fabsf(m_TargetPosition.x - m_Position.x) <= distance) {
				m_Position = m_TargetPosition;
			}
			else {
				m_Position.x += distance * xDirection;
			}
		}
	}

	void WorkerElement::setJob(const JobElement& _job) {
		m_Job = _job;
		m_TargetPosition = m_Job.getWorkPosition();
	}
}