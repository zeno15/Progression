#include <Driller/Managers/ResourceManager.hpp>

#include <iostream>
#include <cassert>

namespace Driller {
	const std::string ResourceManager::Name = "ResourceManager";

	ResourceManager::ResourceManager(void) :
		m_Ore(0),
		m_Money(0) {

	}


	unsigned int ResourceManager::getOre(void) const {
		return m_Ore;
	}
	void ResourceManager::addOre(unsigned int _amount) {
		m_Ore += _amount;
		std::cout << "Added " << _amount << " ore to " << m_Ore << std::endl;
	}
	void ResourceManager::removeOre(unsigned int _amount) {
		assert(m_Ore >= _amount);
		m_Ore -= _amount;
		std::cout << "Removed " << _amount << " ore to " << m_Ore << std::endl;
	}


	unsigned int ResourceManager::getMoney(void) const {
		return m_Money;
	}
	void ResourceManager::addMoney(unsigned int _amount) {
		m_Money += _amount;
		std::cout << "Added " << _amount << " money to " << m_Money << std::endl;
	}
	void ResourceManager::removeMoney(unsigned int _amount) {
		assert(m_Money >= _amount);
		m_Money -= _amount;
		std::cout << "Removed " << _amount << " money to " << m_Money << std::endl;
	}
}