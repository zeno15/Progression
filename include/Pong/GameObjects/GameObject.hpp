#ifndef INCLUDED_PONG_GAME_OBJECTS_GAME_OBJECT_HPP_
#define INCLUDED_PONG_GAME_OBJECTS_GAME_OBJECT_HPP_

#include <Graphics/Renderable.hpp>

#include <string>

////////////////////////////////////////////////////////////
///
///	\namespace Pong
///
////////////////////////////////////////////////////////////
namespace Pong {
	////////////////////////////////////////////////////////////
	///
	///	\brief	Base class for all game objects
	///
	////////////////////////////////////////////////////////////
	class GameObject : public Graphics::Renderable {
	public:

		///////////////////////////////////////////////////////////////
		///
		///	\brief	Constructor
		///
		////////////////////////////////////////////////////////////
		GameObject(void);

		///////////////////////////////////////////////////////////////
		///
		///	\brief	Constructor
		///
		///	\param	The Game Objects name
		///
		////////////////////////////////////////////////////////////
		GameObject(const std::string& _name);

		////////////////////////////////////////////////////////////
		///
		///	\brief	Desctructor
		///
		////////////////////////////////////////////////////////////
		virtual ~GameObject(void);


		////////////////////////////////////////////////////////////
		///
		///	\brief	Updates the game object
		///
		///	\param	The elapsed time for the update
		///
		////////////////////////////////////////////////////////////
		virtual void update(float _delta) = 0;
		////////////////////////////////////////////////////////////
		///
		///	\brief	Pure virtual method to override to allow rendering
		///
		///	\param	The window to render to
		///
		///	\param	The render states to use
		///
		////////////////////////////////////////////////////////////
		virtual void render(const Window::Window& _window, Graphics::RenderData _RenderData) const = 0;


		////////////////////////////////////////////////////////////
		///
		///	\brief	Gets the Game Objects name
		///
		///	\return	The name of the Game Object
		///
		////////////////////////////////////////////////////////////
		const std::string& getName(void) const;

	private:
		std::string				m_Name;				///<	The name of the game object
	};
}

#endif // INCLUDED_PONG_GAME_OBJECTS_GAME_OBJECT_HPP_