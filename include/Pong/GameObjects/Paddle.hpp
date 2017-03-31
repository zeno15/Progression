#ifndef INCLUDED_PONG_GAME_OBJECTS_PADDLE_HPP_
#define INCLUDED_PONG_GAME_OBJECTS_PADDLE_HPP_

#include <Pong/GameObjects/GameObject.hpp>

#include <Pong/PongDefinitions.hpp>

#include <Graphics/Colour.hpp>

////////////////////////////////////////////////////////////
///
///	\namespace Pong
///
////////////////////////////////////////////////////////////
namespace Pong {
	////////////////////////////////////////////////////////////
	///
	///	\brief	Game object to represent paddle
	///
	////////////////////////////////////////////////////////////
	class Paddle : public GameObject {
	public:
		////////////////////////////////////////////////////////////
		///
		///	\brief Constructor
		///
		////////////////////////////////////////////////////////////
		Paddle(void);
		////////////////////////////////////////////////////////////
		///
		///	\brief Constructor
		///
		///	\param	Paddles name
		///
		///	\param	The colour of the paddle
		///
		///	\param	The team the paddle is on
		///
		////////////////////////////////////////////////////////////
		Paddle(const std::string& _name, const Graphics::Colour& _colour, PongDefinitions::PaddleTeam _team);


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
		///	\brief	Renders the paddle
		///
		///	\param	The window to render to
		///
		///	\param	The render states to use
		///
		////////////////////////////////////////////////////////////
		virtual void render(const Window::Window& _window, Graphics::RenderData _renderData) const override;

	private:
		////////////////////////////////////////////////////////////
		///
		///	\brief	Ensures the paddle is restricted to within the board
		///
		////////////////////////////////////////////////////////////
		void clampPaddleToBounds(void);

	private:
		unsigned int						m_VAO;						///<	OpenGL VAO handle
		unsigned int						m_VBO;						///<	OpenGL position VBO handle

		float								m_Offset;					///<	The vertical offset

		Graphics::Colour					m_Colour;					///<	The colour of the paddle

		PongDefinitions::PaddleTeam			m_Team;						///<	The team the paddle is on
	};
}

#endif // INCLUDED_PONG_GAME_OBJECTS_PADDLE_HPP_