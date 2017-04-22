#ifndef INCLUDED_TOWER_MANAGERS_USER_INTERACTION_MANAGER_HPP_
#define INCLUDED_TOWER_MANAGERS_USER_INTERACTION_MANAGER_HPP_

#include <Graphics/RenderData.hpp>
#include <Graphics/Text.hpp>

#include <Infrastructure/Manager.hpp>

#include <Window/Window.hpp>

namespace Tower {
	class UserInteractionManager : public Infrastructure::Manager {
	public:
		friend class InstanceCollection;

		const static std::string Name;		///<	The name of the manager

		UserInteractionManager(void);

		void update(float _delta);
		bool handleEvent(const System::Event& _event);
		void render(const Window::Window& _window, Graphics::RenderData _renderData) const;

	private:
		bool				m_BuildingGhost;
		Graphics::Text		m_MoneyText;
		Graphics::Text		m_LivesText;
	};
}

#endif // INCLUDED_TOWER_MANAGERS_USER_INTERACTION_MANAGER_HPP_