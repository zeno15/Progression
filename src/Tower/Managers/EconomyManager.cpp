#include <Tower/Managers/EconomyManager.hpp>

namespace Tower {
	const std::string EconomyManager::Name = "EconomyManager";

	bool EconomyManager::removeMoney(float _amount) {
		if (m_Money < _amount) {
			return false;
		}

		m_Money -= _amount;
		return true;
	}
	void EconomyManager::addMoney(float _amount) {
		m_Money += _amount;
	}
	float EconomyManager::getMoney(void) const {
		return m_Money;
	}
}