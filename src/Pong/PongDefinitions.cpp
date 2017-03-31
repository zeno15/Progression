#include <Pong/PongDefinitions.hpp>

namespace Pong {
	const float PongDefinitions::PaddleWidth = 8.0f;
	const float PongDefinitions::PaddleHeight = 64.0f; 
	const float PongDefinitions::PaddleBaseSpeed = 256.0f;
	const float PongDefinitions::BoardWidth = 1000.0f;
	const float PongDefinitions::BoardHeight = 600.0f;
	const float PongDefinitions::BoardOutlineThickness = 8.0f;
	const float PongDefinitions::BallSize = 8.0f;
	const float PongDefinitions::BallInitialSpeed = 396.0f;

	float PongDefinitions::toRadians(float _degrees) {
		return 3.14159265f / 180.0f * _degrees;
	}
	float PongDefinitions::toDegrees(float _radians) {
		return _radians * 180.0f / 3.14159265f;
	}

	const System::Keyboard::Key PongDefinitions::KeyBindings[PaddleTeam::NumberOfTeams][KeyBindings::NumberOfKeyBindings] = {
		// Left Player
		{ 
			// Move Up
			System::Keyboard::Key::W,		
			// Move Down
			System::Keyboard::Key::S 
		},

		// Right Player
		{ 
			// Move Up
			System::Keyboard::Key::Up,	
			// Move Down
			System::Keyboard::Key::Down 
		}
	};
}