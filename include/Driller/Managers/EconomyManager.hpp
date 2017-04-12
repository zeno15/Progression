#ifndef INCLUDED_DRILLER_MANAGERS_ECONOMY_MANAGER_HPP_
#define INCLUDED_DRILLER_MANAGERS_ECONOMY_MANAGER_HPP_

#include <Infrastructure/Manager.hpp>

////////////////////////////////////////////////////////////
///
///	\namespace Driller
///
////////////////////////////////////////////////////////////
namespace Driller {
	////////////////////////////////////////////////////////////
	///
	///	\brief	Manager for mining operations economy
	///
	////////////////////////////////////////////////////////////
	class EconomyManager : public Infrastructure::Manager {
	public:
		friend class InstanceCollection;

		const static std::string Name;				///<	The name of the manager

		////////////////////////////////////////////////////////////
		///
		///	\brief	Constructor
		///
		////////////////////////////////////////////////////////////
		EconomyManager(void);

		////////////////////////////////////////////////////////////
		///
		///	\brief	Sets the ore to money exchange rate
		///
		///	\param	The new rate
		///
		////////////////////////////////////////////////////////////
		void setOreToMoneyRate(float _rate);
		////////////////////////////////////////////////////////////
		///
		///	\brief	Gets the ore to money exchange rate
		///
		///	\return	The rate
		///
		////////////////////////////////////////////////////////////
		float getOreToMoneyRate(void) const;

	private:
		float	m_OreToMoneyRate;
	};
}

#endif // INCLUDED_DRILLER_MANAGERS_ECONOMY_MANAGER_HPP_