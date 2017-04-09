#ifndef INCLUDED_DRILLER_MANAGERS_RESOURCE_MANAGER_HPP_
#define INCLUDED_DRILLER_MANAGERS_RESOURCE_MANAGER_HPP_

#include <Infrastructure/Manager.hpp>

////////////////////////////////////////////////////////////
///
///	\namespace Driller
///
////////////////////////////////////////////////////////////
namespace Driller {
	////////////////////////////////////////////////////////////
	///
	///	\brief	Manager for mining operations resources
	///
	////////////////////////////////////////////////////////////
	class ResourceManager : public Infrastructure::Manager {
	public:
		friend class InstanceCollection;

		const static std::string Name;				///<	The name of the manager

		////////////////////////////////////////////////////////////
		///
		///	\brief	Constructor
		///
		////////////////////////////////////////////////////////////
		ResourceManager(void);

	private:
		unsigned int		m_Ore;					///<	The amount of ore the operation has 
	};
}

#endif // INCLUDED_DRILLER_MANAGERS_RESOURCE_MANAGER_HPP_