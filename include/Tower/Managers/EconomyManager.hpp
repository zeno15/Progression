#ifndef INCLUDED_TOWER_MANAGERS_ECONOMY_MANAGER_HPP_
#define INCLUDED_TOWER_MANAGERS_ECONOMY_MANAGER_HPP_


#include <Infrastructure/Manager.hpp>

namespace Tower {
	class EconomyManager : public Infrastructure::Manager {
	public:
		friend class InstanceCollection;

		const static std::string Name;		///<	The name of the manager

		bool removeMoney(float _amount);
		void addMoney(float _amount);
		float getMoney(void) const;

	private:
		float m_Money;
	};
}


#endif // INCLUDED_TOWER_MANAGERS_ECONOMY_MANAGER_HPP_