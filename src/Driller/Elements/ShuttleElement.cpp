#include <Driller/Elements/ShuttleElement.hpp>

#include <Driller/Elements/WorkerElement.hpp>
#include <Driller/Elements/ElementHelpers.hpp>

#include <Driller/DrillerDefinitions.hpp>
#include <Driller/DrillerResources.hpp>

#include <Driller/Managers/EconomyManager.hpp>
#include <Driller/Managers/ResourceManager.hpp>
#include <Driller/Managers/WorkerManager.hpp>

#include <Infrastructure/InstanceCollection.hpp>
#include <Infrastructure/TextureManager.hpp>

#include <System/VectorMath.hpp>

#include <iostream>

namespace Driller {
	ShuttleElement::ShuttleElement(void) :
		m_Graphics(DrillerResources::SpriteSheetName),
		m_GoingToLanding(false),
		m_Landed(false),
		m_GoingToDeparture(false), 
		m_Complete(false),
		m_FirstLanding(true),
		m_LandedTime(0.0f) {


		m_Graphics.addAnimation(
			System::Vector2f(
				DrillerDefinitions::TileWidth *  DrillerResources::ShuttleSpriteSize.x,
				DrillerDefinitions::TileHeight * DrillerResources::ShuttleSpriteSize.y),
			System::Vector2f(
				DrillerDefinitions::TileWidth *  DrillerResources::ShuttleSpriteIndex.x,
				DrillerDefinitions::TileHeight * DrillerResources::ShuttleSpriteIndex.y),
			System::Vector2f(
				DrillerDefinitions::TileWidth *  DrillerResources::ShuttleSpriteSize.x,
				DrillerDefinitions::TileHeight * DrillerResources::ShuttleSpriteSize.y));

		m_Graphics.generate();
	}


	void ShuttleElement::update(float _delta) {
		auto speed = 256.0f;

		if (m_GoingToLanding) {
			auto remaining = DrillerDefinitions::ShuttleLandingPoint - m_Graphics.getPosition();
			auto distance = System::length(remaining);
			auto direction = remaining / distance;


			if (distance < _delta * speed) {
				m_Landed = true;
				m_GoingToLanding = false;
				m_Graphics.setTranslate(DrillerDefinitions::ShuttleLandingPoint);

				if (m_FirstLanding) {
					m_FirstLanding = false;
					onFirstLanding();
				}

				std::cout << "Shuttle landed" << std::endl;
				buyOre();
			}
			else {
				m_Graphics.translate(direction * speed * _delta);
			}
		} 
		else if (m_Landed) {
			m_LandedTime += _delta;
			if (canLeave() && m_LandedTime >= DrillerDefinitions::MinimumShuttleLandingTime) {
				m_GoingToDeparture = true;
				m_Landed = false;
			}
		}
		else if (m_GoingToDeparture) {
			auto remaining = DrillerDefinitions::ShuttleEndPoint - m_Graphics.getPosition();
			auto distance = System::length(remaining);
			auto direction = remaining / distance;


			if (distance < _delta * speed) {
				m_GoingToDeparture = false;
				m_Complete = true;
				m_Graphics.setTranslate(DrillerDefinitions::ShuttleEndPoint);
			}
			else {
				m_Graphics.translate(direction * speed * _delta);
			}
		}
	}

	bool ShuttleElement::handleEvent(const System::Event& _event) {
		return false;
	}

	void ShuttleElement::render(const Window::Window& _window, Graphics::RenderData _renderData) const {

		_renderData.shaderName = DrillerResources::AnimatedSpriteShader;
		_renderData.texture = &Infrastructure::InstanceCollection::getInstance<Infrastructure::TextureManager>().getTexture(DrillerResources::SpriteSheetName);
		m_Graphics.render(_window, _renderData);
	}

	void ShuttleElement::resetForArrival(void) {
		m_Graphics.setTranslate(DrillerDefinitions::ShuttleBeginPoint);
		m_GoingToLanding = true;
		m_Landed = false;
		m_GoingToDeparture = false;
		m_Complete = false;
		m_LandedTime = 0.0f;
	}

	bool ShuttleElement::hasFinishedDeparture(void) {
		return m_Complete;
	}

	bool ShuttleElement::canLeave(void) {
		return true;
	}
	
	void ShuttleElement::onFirstLanding(void) {
		createWorker();
	}

	void ShuttleElement::createWorker(void) {
		auto worker = new WorkerElement();
		worker->setPosition(DrillerDefinitions::ShuttleLandingPoint + System::Vector2f(0.0f, -DrillerDefinitions::TileHeight));
		Infrastructure::InstanceCollection::getInstance<WorkerManager>().addWorker(worker);
	}

	void ShuttleElement::buyOre(void) {
		auto& resourceManager = Infrastructure::InstanceCollection::getInstance<ResourceManager>();
		auto& economyManager = Infrastructure::InstanceCollection::getInstance<EconomyManager>();

		unsigned int oreTotal = resourceManager.getOre();
		resourceManager.removeOre(oreTotal);

		unsigned int moneyTotal = static_cast<unsigned int>(static_cast<float>(oreTotal) * economyManager.getOreToMoneyRate());
		resourceManager.addMoney(moneyTotal);
	}
}