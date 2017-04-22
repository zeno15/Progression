#ifndef INCLUDED_TOWER_GAME_OBJECTS_CREEP_HPP_
#define INCLUDED_TOWER_GAME_OBJECTS_CREEP_HPP_

#include <Tower/GameObjects/GameObject.hpp>

#include <Graphics/VertexArray.hpp>


namespace Tower {
	class Tile;

	class Creep : public GameObject {
	public:
		Creep(float _health);
		~Creep(void);

		virtual void update(float _delta) override;
		virtual bool handleEvent(const System::Event& _event) override;
		virtual void render(const Window::Window& _window, Graphics::RenderData _renderData) const override;

		void setTile(Tile *_tile);

		bool getIsAlive(void) const;

		void damage(float _amount);
		void heal(float _amount);

		void onDeath(void);

		unsigned int getLivesCost(void) const;

	private:
		void setNextTileTarget(void);

	private:
		bool m_Alive;
		float m_Health;
		float m_MaxHealth;
		float m_Money;
		unsigned int m_LivesCost;
		Graphics::VertexArray m_Graphics;

		Tile *m_Target;
		System::Vector2f m_TargetPosition;
	};
}

#endif // INCLUDED_TOWER_GAME_OBJECTS_CREEP_HPP_