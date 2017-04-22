#include <Tower/GameObjects/Creep.hpp>

#include <Tower/TowerDefinitions.hpp>
#include <Tower/TowerResources.hpp>

#include <Tower/Components/Tile.hpp>

#include <Tower/Managers/EconomyManager.hpp>
#include <Tower/Managers/LevelManager.hpp>
#include <Tower/Managers/NotificationManager.hpp>

#include <Infrastructure/InstanceCollection.hpp>
#include <Infrastructure/ShaderManager.hpp>

#include <System/VectorMath.hpp>

#include <iostream>

#define SPEED 128.0f

namespace Tower {

	Creep::Creep(float _health) :
		m_Alive(true),
		m_Health(_health),
		m_MaxHealth(_health),
		m_LivesCost(1),
		m_Target(nullptr) {
		m_Graphics.addVertex(Graphics::Vertex(System::Vector3f(-TowerDefinitions::TileSize / 2.0f, -TowerDefinitions::TileSize / 2.0f, 0.0f), Graphics::Colour::Magenta));
		m_Graphics.addVertex(Graphics::Vertex(System::Vector3f(+TowerDefinitions::TileSize / 2.0f, -TowerDefinitions::TileSize / 2.0f, 0.0f), Graphics::Colour::Magenta));
		m_Graphics.addVertex(Graphics::Vertex(System::Vector3f(0.0f, +TowerDefinitions::TileSize / 2.0f, 0.0f), Graphics::Colour::Magenta));

		m_Graphics.create();

		m_Money = 1.0f;

		position = System::Vector2f(TowerDefinitions::TileSize / 2.0f, TowerDefinitions::TileSize / 2.0f);
	}
	Creep::~Creep(void) {

	}

	void Creep::update(float _delta) {
		auto distance = System::distance(position, m_TargetPosition);

		auto movement = _delta * SPEED;

		if (distance < movement) {
			position = m_TargetPosition;
			setNextTileTarget();
		}
		else {
			auto dir = System::normalise(m_TargetPosition - position);
			position += dir * _delta * SPEED;
		}
	}

	bool Creep::handleEvent(const System::Event& _event) {
		return false;
	}
	void Creep::render(const Window::Window& _window, Graphics::RenderData _renderData) const {

		auto& shader = Infrastructure::InstanceCollection::getInstance<Infrastructure::ShaderManager>().getShader(TowerResources::VertexArrayNoTextureShaderName);
		shader.bind();
		shader.passUniform(TowerResources::VertexArrayNoTextureShaderUniformMVP,
			_renderData.projection *
			_renderData.view *
			System::Mat4x4::createTranslation(System::Vector3f(position, TowerDefinitions::CreepZ)));

		m_Graphics.render(_window, _renderData);
	}

	void Creep::setTile(Tile *_tile) {
		m_Target = _tile;
		auto newPosition = (System::Vector2f(_tile->x, _tile->y) + System::Vector2f(0.5f, 0.5f)) * TowerDefinitions::TileSize;
		m_TargetPosition = newPosition;
	}

	bool Creep::getIsAlive(void) const {
		return m_Alive;
	}

	void Creep::damage(float _amount) {
		m_Health -= _amount;

		if (m_Alive && m_Health <= 0.0f) {
			m_Alive = false;
			Infrastructure::InstanceCollection::getInstance<NotificationManager>().onCreepKilled.invoke(this);
			onDeath();
		}
	}
	void Creep::heal(float _amount) {
		if (m_Alive) {
			m_Health = std::max(m_MaxHealth, m_Health + _amount);
		}
	}

	void Creep::onDeath(void) {
		Infrastructure::InstanceCollection::getInstance<EconomyManager>().addMoney(m_Money);
	}

	void Creep::setNextTileTarget(void) {
		if (m_Target->type == Tile::Type::End) {
			Infrastructure::InstanceCollection::getInstance<NotificationManager>().onCreepReachesEnd.invoke(this);
			m_Target = nullptr;
			m_Alive = false;
			return;
		}

		if (m_Target->nextTile == System::Vector2i(-1, -1)) {
			throw std::runtime_error("Trying to find next tile but it wasn't set.");
		}

		auto& levelManager = Infrastructure::InstanceCollection::getInstance<LevelManager>();

		setTile(&levelManager.getLevel().getTile(m_Target->nextTile.x, m_Target->nextTile.y));
	}

	unsigned int Creep::getLivesCost(void) const {
		return m_LivesCost;
	}
}