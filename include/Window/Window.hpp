#ifndef INCLUDED_WINDOW_WINDOW_HPP_
#define INCLUDED_WINDOW_WINDOW_HPP_


#include <Window/ContextImplementation.hpp>
#include <Window/WindowImplementation.hpp>
#include <Window/WindowStyle.hpp>

#include <System/Vector2.hpp>

////////////////////////////////////////////////////////////
///
///	\namespace Window	
///
////////////////////////////////////////////////////////////
namespace Window {

	////////////////////////////////////////////////////////////
	///
	///	\brief	Platform independant window representation
	///
	////////////////////////////////////////////////////////////
	class Window {
	public:
		////////////////////////////////////////////////////////////
		///
		///	\brief	Constructor
		///
		////////////////////////////////////////////////////////////
		Window(void);

		////////////////////////////////////////////////////////////
		///
		///	\brief	Constructor internally calls create
		///
		///	\param	The video mode to make the window with
		///
		///	\param	The title for the window
		///
		///	\param	The window style
		///
		////////////////////////////////////////////////////////////
		Window(const VideoMode& _videoMode, const std::string& _title, uint32_t _style = WindowStyle::Default);

		////////////////////////////////////////////////////////////
		///
		///	\brief	Destructor
		///
		////////////////////////////////////////////////////////////
		~Window(void);


		////////////////////////////////////////////////////////////
		///
		///	\brief	Creates a window
		///
		///	\param	The video mode to make the window with
		///
		///	\param	The title for the window
		///
		///	\param	The window style
		///
		///	\return	Whether the window was created successfully or not
		///
		////////////////////////////////////////////////////////////
		bool create(const VideoMode& _videoMode, const std::string& _title, uint32_t _style);

		////////////////////////////////////////////////////////////
		///
		///	\brief	Closes the window
		///
		////////////////////////////////////////////////////////////
		void close(void);

		////////////////////////////////////////////////////////////
		///
		///	\brief	Gets whether the window is open
		///
		///	\return	Whether the window is open or not
		///
		////////////////////////////////////////////////////////////
		bool isOpen(void) const;

		////////////////////////////////////////////////////////////
		///
		///	\brief	Gets the position of the window
		///
		///	\return	The position of the window
		///
		////////////////////////////////////////////////////////////
		System::Vector2i getPosition(void) const;

		////////////////////////////////////////////////////////////
		///
		///	\brief	Sets the position of the window
		///
		///	\param	The new position of the window
		///
		////////////////////////////////////////////////////////////
		void setPosition(const System::Vector2i& _position);

		////////////////////////////////////////////////////////////
		///
		///	\brief	Gets the size of the window
		///
		///	\return	The size of the window
		///
		////////////////////////////////////////////////////////////
		System::Vector2u getSize(void) const;

		////////////////////////////////////////////////////////////
		///
		///	\brief	Sets the size of the window
		///
		///	\param	The size of the window
		///
		////////////////////////////////////////////////////////////
		void setSize(const System::Vector2u& _size);

		////////////////////////////////////////////////////////////
		///
		///	\brief	Displays the contents of the window
		///
		////////////////////////////////////////////////////////////
		void display(void);

		////////////////////////////////////////////////////////////
		//
		//	Returns whether or not there are any unprocessed events
		//	in the queue, if there are it modifies the given event
		//
		////////////////////////////////////////////////////////////
		bool pollEvent(System::Event& _event);
		////////////////////////////////////////////////////////////
		//
		//	Waits for an event to enter the queue, modifies the 
		//	given event
		//
		////////////////////////////////////////////////////////////
		void waitEvent(System::Event& _event);

		////////////////////////////////////////////////////////////
		//
		//	Sets whether repeated key input is being used
		//
		////////////////////////////////////////////////////////////
		void setRepeatedKeys(bool _repeat);

		////////////////////////////////////////////////////////////
		///
		///	\brief	Clears the window
		///
		////////////////////////////////////////////////////////////
		void clear(void);

		////////////////////////////////////////////////////////////
		//
		//	Returns the system specific window handle
		//
		////////////////////////////////////////////////////////////
		WindowHandle getHandle(void) const;

		////////////////////////////////////////////////////////////
		//
		//	Sets the title of the window
		//
		////////////////////////////////////////////////////////////
		void setTitle(const std::string& _title);

		////////////////////////////////////////////////////////////
		//
		//	Gets the current title of the window
		//
		////////////////////////////////////////////////////////////
		std::string getTitle(void) const;

	protected:
		uint32_t				m_WindowStyle;
		VideoMode				m_VideoMode;
		std::string				m_Title;

		WindowImplementation	m_WindowImpl;
		ContextImplementation	m_ContextImpl;
	};

}

#endif // INCLUDED_WINDOW_WINDOW_HPP_