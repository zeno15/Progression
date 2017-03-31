#include <Driller/Elements/JobElement.hpp>

#include <Infrastructure/InstanceCollection.hpp>
#include <Infrastructure/ShaderManager.hpp>
#include <Infrastructure/TextureManager.hpp>

#include <Driller/DrillerDefinitions.hpp>
#include <Driller/DrillerResources.hpp>

#include <Driller/Elements/ElementHelpers.hpp>

#include <Driller/Scenes/DrillerGameScene.hpp>

#include <Window/OpenGL.hpp>

namespace Driller {
	JobElement::JobElement(const std::string& _jobName) :
		JobElement(_jobName, System::Vector2i()) {
	}

	JobElement::JobElement(const std::string& _jobName, const System::Vector2i& _tileCoordinates) :
		JobElement(_jobName, _tileCoordinates, System::Vector2f(_tileCoordinates.x * DrillerDefinitions::TileWidth, _tileCoordinates.y * DrillerDefinitions::TileHeight)) {

	}

	JobElement::JobElement(const std::string& _jobName, const System::Vector2i& _tileCoordinates, const System::Vector2f& _workPosition) :
		JobElement(_jobName, _tileCoordinates, _workPosition, DrillerDefinitions::JobType::Instant) {
	}

	JobElement::JobElement(const std::string& _jobName, const System::Vector2i& _tileCoordinates, const System::Vector2f& _workPosition, DrillerDefinitions::JobType _jobType) :
		m_JobName(_jobName),
		m_TileCoordinates(_tileCoordinates),
		m_WorkPosition(_workPosition),
		m_JobType(_jobType),
		m_RemainingTime(0.0f),
		m_RemainingAmount(0),
		m_VAO(0), 
		m_VBO(0) {

		ElementHelpers::createBasicDoubleTriQuadForTextureId(DrillerResources::JobPendingSpriteIndex, &m_VAO, &m_VBO);

	}

	JobElement::~JobElement(void) {
	}


	void JobElement::render(const Window::Window& _window, Graphics::RenderData _renderData) const {
		auto& shader = Infrastructure::InstanceCollection::getInstance<Infrastructure::ShaderManager>().getShader(DrillerResources::StaticTexturedShaderName);
		shader.bind();
		shader.passUniform(DrillerResources::StaticTexturedShaderMVPUniformName, _renderData.projection * _renderData.view * System::Mat4x4::createTranslation(System::Vector3f(DrillerDefinitions::TileHeight * m_TileCoordinates.x, -DrillerDefinitions::TileHeight * m_TileCoordinates.y, 0.1f)));
		Infrastructure::InstanceCollection::getInstance<Infrastructure::TextureManager>().getTexture(DrillerResources::SpriteSheetName).bind();
		glBindVertexArray(m_VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}


	bool JobElement::workTimedJob(float _delta) {
		reduceRemainingTime(_delta);

		return m_RemainingTime <= 0.0f;
	}

	std::string JobElement::getJobName(void) const {
		return m_JobName;
	}

	System::Vector2i JobElement::getTileCoordinates(void) const {
		return m_TileCoordinates;
	}

	System::Vector2f JobElement::getWorkPosition(void) const {
		return m_WorkPosition;
	}

	DrillerDefinitions::JobType JobElement::getJobType(void) const {
		return m_JobType;
	}


	void JobElement::setRemaingTime(float _remainingTime) {
		m_RemainingTime = _remainingTime;
	}
	void JobElement::reduceRemainingTime(float _reduction) {
		m_RemainingTime -= _reduction;
		if (m_RemainingTime < 0.0f) {
			m_RemainingTime = 0.0f;
		}
	}
	float JobElement::getRemainingTime(void) const {
		return m_RemainingTime;
	}


	void JobElement::setRemainingAmount(unsigned int _remainingAmount) {
		m_RemainingAmount = _remainingAmount;
	}
	void JobElement::reduceRemainingAmount(unsigned int _reduction) {
		if (m_RemainingAmount < _reduction) {
			m_RemainingAmount = 0;
		}
		else {
			m_RemainingAmount -= _reduction;
		}
	}
	unsigned int JobElement::getRemainingAmount(void) const {
		return m_RemainingAmount;
	}

	void JobElement::completeJob(void) {
		onJobComplete.invoke(*this);
		m_JobName = "";
		glDeleteBuffers(1, &m_VBO);
		glDeleteVertexArrays(1, &m_VAO);
	}
	bool JobElement::isAccessable(DrillerGameScene& _scene) const {
		auto lastElevatorLevel = _scene.getLastBuiltElevatorLevel();
		if (m_TileCoordinates.y > lastElevatorLevel) {
			return false;
		}

		auto tiles = _scene.getTilesFromElevatorToTarget(m_TileCoordinates.x, m_TileCoordinates.y);

		for (auto& t : tiles) {
			if (t->getColumn() != m_TileCoordinates.x &&
				!t->getIsClear()) {
				return false;
			}
		}

		return true;
	}
}