#ifndef INCLUDED_DRILLER_DRILLER_START_HPP_
#define INCLUDED_DRILLER_DRILLER_START_HPP_


////////////////////////////////////////////////////////////
///
///	\namespace Driller
///
////////////////////////////////////////////////////////////
namespace Driller {
	////////////////////////////////////////////////////////////
	///
	///	\brief	Populates instance collection with Driller managers
	///
	////////////////////////////////////////////////////////////
	void initialiseManagers(void);

	////////////////////////////////////////////////////////////
	///
	///	\brief	Binds callbacks necessary for duration
	///
	////////////////////////////////////////////////////////////
	void bindCallbacks(void);

	////////////////////////////////////////////////////////////
	///
	///	\brief	Loads resources needed for Driller
	///
	////////////////////////////////////////////////////////////
	void loadResources(void);

	////////////////////////////////////////////////////////////
	///
	///	\brief	Starts Driller
	///
	////////////////////////////////////////////////////////////
	void start(void);
}

#endif // INCLUDED_DRILLER_DRILLER_START_HPP_