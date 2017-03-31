#ifndef INCLUDED_DRILLER_SCENES_DRILLER_GAME_SCENE_HPP_
#define INCLUDED_DRILLER_SCENES_DRILLER_GAME_SCENE_HPP_

#include <Infrastructure/Scene.hpp>

#include <Driller/Elements/ElevatorShaftElement.hpp>
#include <Driller/Elements/UndergroundTileElement.hpp>

#include <vector>

////////////////////////////////////////////////////////////
///
///	\namespace Driller
///
////////////////////////////////////////////////////////////
namespace Driller {

	class DrillerGameScene : public Infrastructure::Scene {
	public:
		////////////////////////////////////////////////////////////
		///
		///	\brief	Constructor
		///	
		////////////////////////////////////////////////////////////
		DrillerGameScene(void);
		////////////////////////////////////////////////////////////
		///
		///	\brief	Destructor
		///	
		////////////////////////////////////////////////////////////
		~DrillerGameScene(void);

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
		///	\brief	Gets a pointer to the elevator at the given level
		///
		///	\param	The level to get the elevator at
		///
		///	\return	Pointer to the elevator, nullptr if doesn't exist
		///
		////////////////////////////////////////////////////////////
		ElevatorShaftElement *getElevator(int _level);

		////////////////////////////////////////////////////////////
		///
		///	\brief	Gets a pointer to the tile at the given level and column
		///
		///	\param	The column to get the tile at
		///
		///	\param	The level to get the tile at
		///
		///	\return	Pointer to the tile, nullptr if doesn't exist
		///
		////////////////////////////////////////////////////////////
		UndergroundTileElement *getTile(int _column, int _level);

		////////////////////////////////////////////////////////////
		///
		///	\brief	Gets the level of the last built elevator
		///
		///	\return The level
		///
		////////////////////////////////////////////////////////////
		int getLastBuiltElevatorLevel(void) const;

		////////////////////////////////////////////////////////////
		///
		///	\brief	Gets the tiles from the elevator to the target tile
		///
		///	\param	The column of the target tile
		///
		///	\param	The level of the target tile
		///
		///	\return	Vector of the tiles to the target, including the target
		///
		////////////////////////////////////////////////////////////
		std::vector<UndergroundTileElement *> getTilesFromElevatorToTarget(int _column, int _level);

		////////////////////////////////////////////////////////////
		///
		///	\brief	Gets whether the given set of tiles are free and valid
		///
		///	\param	The bottom left tile
		///
		///	\param	The size of the set of tiles
		///
		///	\return	Whether all the tiles are free and clear
		///
		////////////////////////////////////////////////////////////
		bool isValid(const System::Vector2i& _bottomLeftTile, const System::Vector2u& _size);

	private:
		std::vector<ElevatorShaftElement *>							m_ElevatorShafts;				///<	Collection of elevator shafts
		std::vector<std::vector<UndergroundTileElement *>>			m_LeftTiles;					///<	The tiles to the left of the elevator
		std::vector<std::vector<UndergroundTileElement *>>			m_RightTiles;					///<	The tiles to the right of the elevator
		unsigned int												m_VAO;							///<	OpenGL VAO handle
		unsigned int												m_VBO;							///<	OpenGL VBO handle
	};
}

#endif // INCLUDED_DRILLER_SCENES_DRILLER_GAME_SCENE_HPP_