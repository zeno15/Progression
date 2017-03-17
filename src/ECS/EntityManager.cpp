#include <ECS/EntityManager.hpp>

#include <Infrastructure/InstanceCollection.hpp>

#include <iostream>
#include <algorithm>

#define ENTITY_COUNT 1000

namespace ECS {

	const std::string EntityManager::Name = "EntityManager";

	EntityManager::EntityManager() :
		m_NextUnassignedId(1) {
		m_Entities.reserve(ENTITY_COUNT);
		m_Entities.emplace_back(0);
	}

	EntityManager::~EntityManager() {
	}


	Entity& EntityManager::createEntity(void) {
		return Infrastructure::InstanceCollection::getInstance<EntityManager>().createSingleEntity();
	}
	Entity& EntityManager::createSingleEntity(void) {
		if (m_ReUsableKeys.size() > 0) {
			unsigned int reusedId = m_ReUsableKeys.back();
			m_ReUsableKeys.pop_back();

			Entity& e = m_Entities[reusedId];
			e.revive();
			return e;
		}

		unsigned int nextKey = m_NextUnassignedId++;
		assert(nextKey < ENTITY_COUNT);

		m_Entities.emplace_back(nextKey);

		return m_Entities[nextKey];
	}
	Entity& EntityManager::getEntity(unsigned int _id) {
		assert(_id < m_Entities.size());
		assert(_id > 0);
		return m_Entities[_id];
	}
	void EntityManager::killEntity(Entity& _entity) {
		killEntity(_entity.getId());
	}
	void EntityManager::killEntity(unsigned int _id) {
		auto& e = getEntity(_id);
		entityKilled.invoke(_id);
		e.kill();
		m_ReUsableKeys.push_back(_id);
	}

	void EntityManager::cleanupEntities(void) {
		for (unsigned int i = 0; i < m_Entities.size(); i += 1) {
			if (m_Entities[i].getToBeRemoved()) {
				killEntity(i);
			}
		}
	}

	unsigned int EntityManager::getNextUnassignedId(void) const {
		return m_NextUnassignedId;
	}

    std::vector<unsigned int> EntityManager::getAliveEntityIds(void) const {
    	auto results = std::vector<unsigned int>();

		for (unsigned int i = 1; i < m_Entities.size(); i += 1) {
    		if (m_Entities[i].isAlive()) {
    			results.push_back(m_Entities[i].getId());
    		}
    	}

    	return results;
    }
}

