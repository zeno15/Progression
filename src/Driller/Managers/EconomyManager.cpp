#include <Driller/Managers/EconomyManager.hpp>


namespace Driller {
	const std::string EconomyManager::Name = "EconomyManager";

	EconomyManager::EconomyManager(void) :
		m_OreToMoneyRate(1.0f) {

	}


	void EconomyManager::setOreToMoneyRate(float _rate) {
		m_OreToMoneyRate = _rate;
	}
	float EconomyManager::getOreToMoneyRate(void) const {
		return m_OreToMoneyRate;
	}

}