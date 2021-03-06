#ifndef INCLUDED_INFRASTRUCTURE_APPLICATION_HPP_
#define INCLUDED_INFRASTRUCTURE_APPLICATION_HPP_

#include <string>

#include <Infrastructure/Manager.hpp>

#include <System/Vector2.hpp>

#include <Window/Window.hpp>

////////////////////////////////////////////////////////////
///
///	\namespace Infrastructure
///
////////////////////////////////////////////////////////////
namespace Infrastructure {

	////////////////////////////////////////////////////////////
	///
	///	\brief	Class to manage update/handle events and render
	///
	////////////////////////////////////////////////////////////
	class Application : public Manager {
	public:
		friend class InstanceCollection;

		const static std::string Name;			///<	Name of the manager

		////////////////////////////////////////////////////////////
		///
		///	\brief	Initialises the application
		///
		///	\param	The starting window size
		///
		///	\param	The starting window title
		///
		////////////////////////////////////////////////////////////
		void initialise(const System::Vector2u& _size, const std::string& _title);

		////////////////////////////////////////////////////////////
		///
		///	\brief	Starts the application
		///
		////////////////////////////////////////////////////////////
		void start(void);

		////////////////////////////////////////////////////////////
		///
		///	\brief	Stops the application
		///
		////////////////////////////////////////////////////////////
		void stop(void);

		////////////////////////////////////////////////////////////
		///
		///	\brief	Gets the application window
		///
		///	\return	The application window
		///
		////////////////////////////////////////////////////////////
		Window::Window& getWindow(void);

		////////////////////////////////////////////////////////////
		///
		///	\brief	Gets whether the application is running
		///
		///	\return Whether the application is running
		///
		////////////////////////////////////////////////////////////
		bool isRunning(void) const;

	private:
		////////////////////////////////////////////////////////////
		///
		///	\brief	Constructor
		///
		////////////////////////////////////////////////////////////
		Application();
		////////////////////////////////////////////////////////////
		///
		///	\brief	Destructor
		///
		////////////////////////////////////////////////////////////
		~Application();

		////////////////////////////////////////////////////////////
		///
		///	\brief	Updates the application
		///
		///	\param	The elapsed time to update
		///
		////////////////////////////////////////////////////////////
		void update(float _delta);
		////////////////////////////////////////////////////////////
		///
		///	\brief	Renders the application
		///
		///	\param	The current alpha value
		///
		////////////////////////////////////////////////////////////
		void render(float _alpha);

		bool m_Running;						///<	Whether the windows is and should keep running

		Window::Window m_Window;			///<	The application window
	};
}

#endif // INCLUDED_INFRASTRUCTURE_APPLICATION_HPP_