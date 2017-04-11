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

		////////////////////////////////////////////////////////////
		///
		///	\brief	Gets the stockpiled ore amount
		///
		///	\return The amount of ore stockpiled
		///
		////////////////////////////////////////////////////////////
		unsigned int getOre(void) const;
		////////////////////////////////////////////////////////////
		///
		///	\brief	Adds ore to the stockpile
		///
		///	\param	The amount to add
		///
		////////////////////////////////////////////////////////////
		void addOre(unsigned int _amount);
		////////////////////////////////////////////////////////////
		///
		///	\brief	Removes ore from the stockpile
		///
		///	\param	The amount to remove
		///
		////////////////////////////////////////////////////////////
		void removeOre(unsigned int _amount);


		////////////////////////////////////////////////////////////
		///
		///	\brief	Gets the stockpiled money
		///
		///	\return The amount of money stockpiled
		///
		////////////////////////////////////////////////////////////
		unsigned int getMoney(void) const;
		////////////////////////////////////////////////////////////
		///
		///	\brief	Adds money to the stockpile
		///
		///	\param	The amount to add
		///
		////////////////////////////////////////////////////////////
		void addMoney(unsigned int _amount);
		////////////////////////////////////////////////////////////
		///
		///	\brief	Removes money from the stockpile
		///
		///	\param	The amount to remove
		///
		////////////////////////////////////////////////////////////
		void removeMoney(unsigned int _amount);


	private:
		unsigned int		m_Ore;					///<	The amount of ore the operation has 
		unsigned int		m_Money;				///<	The amount of money the operation has
	};
}

#endif // INCLUDED_DRILLER_MANAGERS_RESOURCE_MANAGER_HPP_