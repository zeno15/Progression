#ifndef INCLUDED_PONG_GAME_OBJECTS_BALL_HPP_
#define INCLUDED_PONG_GAME_OBJECTS_BALL_HPP_

#include <Pong/GameObjects/GameObject.hpp>

////////////////////////////////////////////////////////////
///
///	\namespace Pong
///
////////////////////////////////////////////////////////////
namespace Pong {
	////////////////////////////////////////////////////////////
	///
	///	\brief	Game object to represent a ball
	///
	////////////////////////////////////////////////////////////
	class Ball : public GameObject {
	public:
		////////////////////////////////////////////////////////////
		///
		///	\brief	Constructor
		///
		////////////////////////////////////////////////////////////
		Ball(void);

		////////////////////////////////////////////////////////////
		///
		///	\brief	Updates the game object
		///
		///	\param	The elapsed time for the update
		///
		////////////////////////////////////////////////////////////
		virtual void update(float _delta) override;
		////////////////////////////////////////////////////////////
		///
		///	\brief	Renders the game object
		///
		///	\param	The window to render to
		///
		///	\param	The render states to use
		///
		////////////////////////////////////////////////////////////
		virtual void render(const Window::Window& _window, Graphics::RenderData _renderData) const override;

		////////////////////////////////////////////////////////////
		///
		///	\brief	Gets the position of the ball
		///
		///	return The position of the ball
		///
		////////////////////////////////////////////////////////////
		const System::Vector2f& getPosition(void) const;
		////////////////////////////////////////////////////////////
		///
		///	\brief	Sets the balls position
		///
		///	\param	The position
		///
		////////////////////////////////////////////////////////////
		void setPosition(const System::Vector2f& _position);
		////////////////////////////////////////////////////////////
		///
		///	\brief	Gets the velocity of the ball
		///
		///	\return The velocity of the ball
		///
		////////////////////////////////////////////////////////////
		const System::Vector2f& getVelocity(void) const;
		////////////////////////////////////////////////////////////
		///
		///	\brief	Sets the balls velocity
		///
		///	\param	The velocity
		///
		////////////////////////////////////////////////////////////
		void setVelocity(const System::Vector2f& _velocity);


	private:
		unsigned int						m_VAO;						///<	OpenGL VAO handle
		unsigned int						m_VBO;						///<	OpenGL position VBO handle

		System::Vector2f					m_Position;					///<	The balls position
		System::Vector2f					m_Velocity;					///<	The balls velocity
	};
}

#endif // INCLUDED_PONG_GAME_OBJECTS_BALL_HPP_