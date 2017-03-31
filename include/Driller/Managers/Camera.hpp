#ifndef INCLUDED_DRILLER_MANAGERS_CAMERA_HPP_
#define INCLUDED_DRILLER_MANAGERS_CAMERA_HPP_

#include <Infrastructure/Manager.hpp>

#include <System/Vector2.hpp>

namespace System {
	class Event;
}

////////////////////////////////////////////////////////////
///
///	\namespace Driller
///
////////////////////////////////////////////////////////////
namespace Driller {
	////////////////////////////////////////////////////////////
	///
	///	\brief	Camera for 2d side scroller Driller
	///
	////////////////////////////////////////////////////////////
	class Camera : public Infrastructure::Manager {
	public:
		friend class InstanceCollection;

		const static std::string Name;		///<	The name of the manager


		////////////////////////////////////////////////////////////
		///
		///	\brief	Constructor
		///
		////////////////////////////////////////////////////////////
		Camera(void);


		////////////////////////////////////////////////////////////
		///
		///	\brief	Handles an event for the camera
		///
		///	\param	The event to handle
		///
		///	\return	Whether the event was handled or not
		///
		////////////////////////////////////////////////////////////
		bool handleEvent(const System::Event& _event);

		////////////////////////////////////////////////////////////
		///
		///	\brief	Moves the camera
		///
		///	\param	The offset to move the camera by
		///
		////////////////////////////////////////////////////////////
		void move(const System::Vector2f& _offset);

		////////////////////////////////////////////////////////////
		///
		///	\brief	Sets the position of the camera
		///
		///	\param	The position to set the camera to
		///
		////////////////////////////////////////////////////////////
		void setPosition(const System::Vector2f& _position);

		////////////////////////////////////////////////////////////
		///
		///	\brief	Gets the position of the camera
		///
		///	\return	The position of the camera
		///
		////////////////////////////////////////////////////////////
		const System::Vector2f& getPosition(void) const;


		////////////////////////////////////////////////////////////
		///
		///	\brief	Zooms the camera
		///
		///	\param	The factor to change the zoom by
		///
		////////////////////////////////////////////////////////////
		void zoom(float _zoom);

		////////////////////////////////////////////////////////////
		///
		///	\brief	Sets the zoom of the camera
		///
		///	\param	The zoom factor to set
		///
		////////////////////////////////////////////////////////////
		void setZoom(float _zoom);

		////////////////////////////////////////////////////////////
		///
		///	\brief	Gets the cameras zoom factor
		///
		///	\return	The zoom factor of the camera
		///
		////////////////////////////////////////////////////////////
		const float getZoom(void) const;

	private:
		System::Vector2f		m_Position;			///<	The position of the camera
		float					m_Zoom;				///<	The zoom level of the camera
	};
}

#endif // INCLUDED_DRILLER_MANAGERS_CAMERA_HPP_