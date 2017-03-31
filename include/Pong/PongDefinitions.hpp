#ifndef INCLUDED_PONG_PONG_DEFINITIONS_HPP_
#define INCLUDED_PONG_PONG_DEFINITIONS_HPP_

#include <string>

#include <System/Keyboard.hpp>

namespace Pong {
	////////////////////////////////////////////////////////////
	///
	///	\brief	Definitions for Pong
	///
	////////////////////////////////////////////////////////////
	class PongDefinitions {
	public:
		static const float PaddleWidth;
		static const float PaddleHeight;
		static const float PaddleBaseSpeed;
		static const float BoardWidth;
		static const float BoardHeight;
		static const float BoardOutlineThickness;
		static const float BallSize;
		static const float BallInitialSpeed;

		static float toRadians(float _degrees);
		static float toDegrees(float _radians);

		enum PaddleTeam {
			Left,
			Right,
			NumberOfTeams
		};
		enum KeyBindings {
			MoveUp,
			MoveDown,
			NumberOfKeyBindings
		};


		static const System::Keyboard::Key KeyBindings[PaddleTeam::NumberOfTeams][KeyBindings::NumberOfKeyBindings];
	};

}

#endif // INCLUDED_PONG_PONG_DEFINITIONS_HPP_