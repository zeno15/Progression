#ifndef INCLUDED_PONG_MANAGERS_GAME_OBJECT_MANAGERS_HPP_
#define INCLUDED_PONG_MANAGERS_GAME_OBJECT_MANAGERS_HPP_

#include <Infrastructure/Manager.hpp>

#include <Pong/GameObjects/GameObject.hpp>

namespace Window {
	class Window;
}

namespace Graphics {
	class RenderData;
}

////////////////////////////////////////////////////////////
///
///	\namespace Pong
///
////////////////////////////////////////////////////////////
namespace Pong {
	////////////////////////////////////////////////////////////
	///
	///	\brief	Manager for all game objects
	///
	////////////////////////////////////////////////////////////
	class GameObjectManager : public Infrastructure::Manager {
	public:
		friend class InstanceCollection;

		const static std::string Name;		///<	The name of the manager


		////////////////////////////////////////////////////////////
		///
		///	\brief	Updates the manager
		///
		///	\param	The elapsed time for the update
		///
		////////////////////////////////////////////////////////////
		void update(float _delta);
		////////////////////////////////////////////////////////////
		///
		///	\brief	Renders the manager
		///
		///	\param	The window to render to
		///
		///	\param	The render states to use
		///
		////////////////////////////////////////////////////////////
		void render(const Window::Window& _window, Graphics::RenderData _RenderData) const;

		////////////////////////////////////////////////////////////
		///
		///	\brief	Adds a game object
		///
		///	\param	The game object
		///
		////////////////////////////////////////////////////////////
		void addGameObject(GameObject *_obj);

		////////////////////////////////////////////////////////////
		///
		///	\brief	Gets a game object by name
		///
		///	\param	The name of the game object to retrieve
		///
		///	\return	The game object
		///
		////////////////////////////////////////////////////////////
		GameObject *getGameObject(const std::string& _name);

		////////////////////////////////////////////////////////////
		///
		///	\brief	Removes a game object from the manager
		///
		///	\param	The object to remove
		///
		////////////////////////////////////////////////////////////
		void removeGameObject(GameObject *_object);

	private:
		std::vector<GameObject *> m_GameObjects;						///<	Game objects
		std::vector<GameObject *> m_GameObjectsToDelete;				///<	Game objects that need to be deleted
	};
}

#endif // INCLUDED_PONG_MANAGERS_GAME_OBJECT_MANAGERS_HPP_