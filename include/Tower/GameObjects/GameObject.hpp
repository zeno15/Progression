#ifndef INCLUDED_TOWER_GAME_OBJECTS_GAME_OBJECT_HPP_
#define INCLUDED_TOWER_GAME_OBJECTS_GAME_OBJECT_HPP_

#include <Graphics/RenderData.hpp>
#include <System/Event.hpp>
#include <System/Vector2.hpp>
#include <Window/Window.hpp>

namespace Tower {
	class GameObject {
	public:
		GameObject(void);
		virtual ~GameObject(void);

		virtual void update(float _delta) = 0;
		virtual bool handleEvent(const System::Event& _event) = 0;
		virtual void render(const Window::Window& _window, Graphics::RenderData _renderData) const = 0;

		System::Vector2f position;
	};
}

#endif // INCLUDED_TOWER_GAME_OBJECTS_GAME_OBJECT_HPP_