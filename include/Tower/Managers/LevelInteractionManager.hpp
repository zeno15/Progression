#ifndef INCLUDED_TOWER_MANAGERS_LEVEL_INTERACTION_MANAGER_HPP_
#define INCLUDED_TOWER_MANAGERS_LEVEL_INTERACTION_MANAGER_HPP_

#include <Graphics/RenderData.hpp>

#include <Infrastructure/Manager.hpp>

#include <System/Vector2.hpp>

#include <Window/Window.hpp>

namespace Tower {
	class LevelInteractionManager : public Infrastructure::Manager {
	public:
		friend class InstanceCollection;

		const static std::string Name;		///<	The name of the manager

		LevelInteractionManager(void);

		static bool isMousePositionWithinLevelBounds(const System::Vector2f& _mousePosition);
		static System::Vector2i getTileCoordinatesFromMousePosition(const System::Vector2f& _mousePosition);
		static System::Vector2i getCurrentMouseTileCoordinates(void);

		void update(float _delta);
		bool handleEvent(const System::Event& _event);
		void render(const Window::Window& _window, Graphics::RenderData _renderData) const;

	};
}

#endif // INCLUDED_TOWER_MANAGERS_LEVEL_INTERACTION_MANAGER_HPP_