#include <Tower/Managers/UserInteractionManager.hpp>
#include <Tower/Managers/EconomyManager.hpp>

#include <Tower/TowerDefinitions.hpp>
#include <Tower/TowerResources.hpp>

#include <Infrastructure/FontManager.hpp>
#include <Infrastructure/InstanceCollection.hpp>
#include <Tower/Managers/LevelInteractionManager.hpp>
#include <Tower/Managers/LevelManager.hpp>
#include <Tower/Managers/TowerManager.hpp>

#include <Tower/GameObjects/Towers/BasicTower.hpp>

#include <Graphics/CircleShape.hpp>

namespace Tower {
	const std::string UserInteractionManager::Name = "UserInteractionManager";



	UserInteractionManager::UserInteractionManager(void) :
		m_BuildingGhost(false) {
		m_MoneyText.setColour(Graphics::Colour::Yellow);
		m_LivesText.setColour(Graphics::Colour::Yellow);
	}
	void UserInteractionManager::update(float _delta) {
		if (Infrastructure::InstanceCollection::getInstance<LevelManager>().hasLevel()) {
			auto money = Infrastructure::InstanceCollection::getInstance<EconomyManager>().getMoney();
			auto lives = Infrastructure::InstanceCollection::getInstance<LevelManager>().getLevel().getLivesRemaining();
			m_MoneyText.generateText("Money: " + std::to_string(static_cast<unsigned int>(money)), &Infrastructure::InstanceCollection::getInstance<Infrastructure::FontManager>().getFont(TowerResources::DefaultFontName));
			m_LivesText.generateText("Lives: " + std::to_string(lives), &Infrastructure::InstanceCollection::getInstance<Infrastructure::FontManager>().getFont(TowerResources::DefaultFontName));
		}
	}
	bool UserInteractionManager::handleEvent(const System::Event& _event) {
		if (_event.type == System::Event::KeyDown) {
			if (_event.key.key == System::Keyboard::F5) {
				m_BuildingGhost = true;
				return true;
			}
			if (_event.key.key == System::Keyboard::Escape) {
				m_BuildingGhost = false;
				return true;
			}
		}
		if (_event.type == System::Event::MouseButtonPressed) {
			if (_event.mouseButton.button == System::Mouse::Left) {
				auto position = Infrastructure::InstanceCollection::getInstance<LevelInteractionManager>().getCurrentMouseTileCoordinates();

				auto& tile = Infrastructure::InstanceCollection::getInstance<LevelManager>().getLevel().getTile(position.x, position.y);

				if (tile.canTowerBeBuilt()) {
					Infrastructure::InstanceCollection::getInstance<TowerManager>().addTower(new BasicTower(System::Vector2u(position)));
					m_BuildingGhost = false;
				}
				return true;
			}
		}
		return false;
	}
	void UserInteractionManager::render(const Window::Window& _window, Graphics::RenderData _renderData) const {
		if (m_BuildingGhost) {
			_renderData.model.translate(System::Vector3f(0.0f, 0.0f, TowerDefinitions::GhostZ));

			auto position = Infrastructure::InstanceCollection::getInstance<LevelInteractionManager>().getCurrentMouseTileCoordinates();

			if (position != System::Vector2i(-1, -1)) {
				auto tile = Infrastructure::InstanceCollection::getInstance<LevelManager>().getLevel().getTile(position.x, position.y);

				auto colour = tile.canTowerBeBuilt() ? Graphics::Colour::Green : Graphics::Colour::Red;

				Graphics::CircleShape c(TowerDefinitions::TileSize / 2.0f - 4.0f);
				c.setColour(colour);
				c.setTranslate(System::Vector2f(position) * TowerDefinitions::TileSize + System::Vector2f(TowerDefinitions::TileSize / 2.0f, TowerDefinitions::TileSize / 2.0f));
				c.render(_window, _renderData);
			}

		}
		if (Infrastructure::InstanceCollection::getInstance<LevelManager>().hasLevel()) {
			_renderData.view = System::Mat4x4(1.0f);
			_renderData.projection = System::Mat4x4::Orthographic2D(0.0f, static_cast<float>(_window.getSize().x), static_cast<float>(_window.getSize().y), 0.0f);
			_renderData.model.translate(System::Vector3f(0.0f, static_cast<float>(_window.getSize().y) - 32.0f, TowerDefinitions::UIZ));
			m_MoneyText.render(_window, _renderData);
			_renderData.model.translate(System::Vector3f(0.0f, -32.0f, 0.0f));
			m_LivesText.render(_window, _renderData);
		}
	}
}