#ifndef INCLUDED_INFRASTRUCTURE_SCENE_HPP_
#define INCLUDED_INFRASTRUCTURE_SCENE_HPP_

#include <string>
#include <Graphics/Renderable.hpp>

////////////////////////////////////////////////////////////
///
///	\brief	namespace Infrastructure
///
////////////////////////////////////////////////////////////
namespace Infrastructure {

	////////////////////////////////////////////////////////////
	///
	///	\brief	Class to represent single gameplay scene
	///
	////////////////////////////////////////////////////////////
	class Scene : public Graphics::Renderable {
	public:
		////////////////////////////////////////////////////////////
		///
		///	\brief	Constructor
		///
		///	\param	Unique name of the scene
		///
		////////////////////////////////////////////////////////////
		Scene(const std::string& _name);
		////////////////////////////////////////////////////////////
		///
		///	\brief	Desctructor
		///
		////////////////////////////////////////////////////////////
		~Scene();

		////////////////////////////////////////////////////////////
		///
		///	\brief	Gets the name of the scene
		///
		///	\return	The name of the scene
		///
		////////////////////////////////////////////////////////////
		std::string getName(void) const;

		////////////////////////////////////////////////////////////
		///
		///	\brief	Updates the scene 
		///
		///	\param	The elapsed time for the update
		///
		////////////////////////////////////////////////////////////
		virtual void update(float _delta) = 0;
		////////////////////////////////////////////////////////////
		///
		///	\brief	Handles an event for the scene
		///
		///	\param	The event to handle
		///
		///	\return	Whether the event was handled or not
		///
		////////////////////////////////////////////////////////////
		virtual bool handleEvent(const System::Event& _event) = 0;
		////////////////////////////////////////////////////////////
		///
		///	\brief	Renders the scene
		///
		///	\param	The window to draw on
		///
		///	\param	The states to draw with
		///
		////////////////////////////////////////////////////////////
		virtual void render(const Window::Window& _window, Graphics::RenderData _RenderData) const = 0;


	private:
		std::string m_Name;		///<	The name of the scene
	};

}

#endif // INCLUDED_INFRASTRUCTURE_SCENE_HPP_