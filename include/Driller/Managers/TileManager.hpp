#ifndef INCLUDED_DRILLER_MANAGERS_TILE_MANAGER_HPP_
#define INCLUDED_DRILLER_MANAGERS_TILE_MANAGER_HPP_

#include <Infrastructure/Manager.hpp>

#include <Driller/DrillerDefinitions.hpp>

////////////////////////////////////////////////////////////
///
///	\namespace Driller
///
////////////////////////////////////////////////////////////
namespace Driller {
	////////////////////////////////////////////////////////////
	///
	///	\brief	Manager for tiles
	///
	////////////////////////////////////////////////////////////
	class TileManager : public Infrastructure::Manager {
	public:
		friend class InstanceCollection;

		const static std::string Name;				///<	The name of the manager

		////////////////////////////////////////////////////////////
		///
		///	\brief	Callback for when tiles are activated
		///
		///	\param	The x coordinate of the activated tile
		///
		///	\param	The y coordinate of the activated tile
		///
		///	\param	The context it was activated under
		///
		////////////////////////////////////////////////////////////
		void onTileActivated(int _x, int _y, DrillerDefinitions::TileInteractionContext _context);

	private:


		////////////////////////////////////////////////////////////
		///
		///	\brief	Callback for when a tile is activated with no context
		///
		///	\param	The x coordinate of the activated tile
		///
		///	\param	The y coordinate of the activated tile
		///
		////////////////////////////////////////////////////////////
		void handleNoContextInteraction(int _x, int _y);

		////////////////////////////////////////////////////////////
		///
		///	\brief	Callback for when a tile is activated with reset context
		///
		///	\param	The x coordinate of the activated tile
		///
		///	\param	The y coordinate of the activated tile
		///
		////////////////////////////////////////////////////////////
		void handleResetContextInteraction(int _x, int _y);
	};
}

#endif // INCLUDED_DRILLER_MANAGERS_TILE_MANAGER_HPP_