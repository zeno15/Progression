#ifndef INCLUDED_PONG_SCENES_PONG_GAME_SCENE_HPP_
#define INCLUDED_PONG_SCENES_PONG_GAME_SCENE_HPP_

#include <Infrastructure/Scene.hpp>

#include <Graphics/Text.hpp>

#include <Pong/PongDefinitions.hpp>

namespace Pong {
	class Ball;
}

////////////////////////////////////////////////////////////
///
///	\namespace Pong
///
////////////////////////////////////////////////////////////
namespace Pong {
	////////////////////////////////////////////////////////////
	///
	///	\brief	Main Pong gameplay scene
	///
	////////////////////////////////////////////////////////////
	class PongGameScene : public Infrastructure::Scene {
	public:
		////////////////////////////////////////////////////////////
		///
		///	\brief	Constructor
		///	
		////////////////////////////////////////////////////////////
		PongGameScene(void);
		////////////////////////////////////////////////////////////
		///
		///	\brief	Destructor
		///	
		////////////////////////////////////////////////////////////
		~PongGameScene(void);

		////////////////////////////////////////////////////////////
		///
		///	\brief	Updates the scene 
		///
		///	\param	The elapsed time for the update
		///
		////////////////////////////////////////////////////////////
		void update(float _delta) override;
		////////////////////////////////////////////////////////////
		///
		///	\brief	Handles an event for the scene
		///
		///	\param	The event to handle
		///
		///	\return	Whether the event was handled or not
		///
		////////////////////////////////////////////////////////////
		bool handleEvent(const System::Event& _event) override;
		////////////////////////////////////////////////////////////
		///
		///	\brief	Renders the scene
		///
		///	\param	The window to draw on
		///
		///	\param	The states to draw with
		///
		////////////////////////////////////////////////////////////
		void render(const Window::Window& _window, Graphics::RenderData _renderData) const override;

		////////////////////////////////////////////////////////////
		///
		///	\brief	Handles when a ball is lost
		///
		///	\param	The team that lost
		///
		///	\param	The ball that was lost
		///
		////////////////////////////////////////////////////////////
		void ballLost(const PongDefinitions::PaddleTeam& _losingTeam, Ball *_ball);

	private:
		Graphics::Text			m_LeftPlayerScoreText;
		unsigned int			m_LeftPlayerScore;
		Graphics::Text			m_RightPlayerScoreText;
		unsigned int			m_RightPlayerScore;
	};
}

#endif // INCLUDED_PONG_SCENES_PONG_GAME_SCENE_HPP_