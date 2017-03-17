#include <catch.hpp>

#include <ECS/Component.hpp>
#include <ECS/EntityManager.hpp>
#include <Infrastructure/InstanceCollection.hpp>

#include <utility>
#include <iostream>

namespace ECS {
    namespace EntityManagerTests {
		class TestComponent : public Component {
		public:
			TestComponent(unsigned int _entityId) : Component(_entityId) {}
		};

    	TEST_CASE("EntityManager first available id is 1", "[EntityManager]") {
			Infrastructure::InstanceCollection::clear();
    		Infrastructure::InstanceCollection::registerInstance<EntityManager>();

    		auto id = Infrastructure::InstanceCollection::getInstance<EntityManager>().getNextUnassignedId();
    		auto aliveIds = Infrastructure::InstanceCollection::getInstance<EntityManager>().getAliveEntityIds();

    		REQUIRE(id == 1);
    		REQUIRE(aliveIds.size() == 0);
    	}

    	TEST_CASE("Entity manager creates entity with the same id as the next unassigned if there are none in the reusable list", "[EntityManager]") {
			Infrastructure::InstanceCollection::clear();
    		Infrastructure::InstanceCollection::registerInstance<EntityManager>();

    		auto id = Infrastructure::InstanceCollection::getInstance<EntityManager>().getNextUnassignedId();

    		auto& e = Infrastructure::InstanceCollection::getInstance<EntityManager>().createEntity();

    		REQUIRE(id == e.getId());
    	}

    	TEST_CASE("New entity will be alive and not marked for removal", "[EntityManager]") {
			Infrastructure::InstanceCollection::clear();
    		Infrastructure::InstanceCollection::registerInstance<EntityManager>();

    		auto& e = Infrastructure::InstanceCollection::getInstance<EntityManager>().createEntity();

    		REQUIRE(e.isAlive());
    		REQUIRE_FALSE(e.getToBeRemoved());
    	}

    	TEST_CASE("When entities have been created the manager knows they are alive", "[EntityManager]") {
			Infrastructure::InstanceCollection::clear();
    		Infrastructure::InstanceCollection::registerInstance<EntityManager>();

    		auto& e1 = Infrastructure::InstanceCollection::getInstance<EntityManager>().createEntity();
    		auto& e2 = Infrastructure::InstanceCollection::getInstance<EntityManager>().createEntity();
    		auto& e3 = Infrastructure::InstanceCollection::getInstance<EntityManager>().createEntity();

    		auto aliveIds = Infrastructure::InstanceCollection::getInstance<EntityManager>().getAliveEntityIds();

    		REQUIRE(aliveIds.size() == 3);
    	}

		TEST_CASE("The manager is aware that an entity is not alive after it has been killed", "[EntityManager]") {
			Infrastructure::InstanceCollection::clear();
			Infrastructure::InstanceCollection::registerInstance<EntityManager>();

			auto& e1 = Infrastructure::InstanceCollection::getInstance<EntityManager>().createEntity();

			Infrastructure::InstanceCollection::getInstance<EntityManager>().killEntity(e1);

			auto aliveIds = Infrastructure::InstanceCollection::getInstance<EntityManager>().getAliveEntityIds();

			REQUIRE(aliveIds.size() == 0);
		}

		TEST_CASE("The manager will re-use an old id before creating a new entity", "[EntityManager]") {
			Infrastructure::InstanceCollection::clear();
			Infrastructure::InstanceCollection::registerInstance<EntityManager>();

			auto& e1 = Infrastructure::InstanceCollection::getInstance<EntityManager>().createEntity();
			unsigned int e1Id = e1.getId();

			Infrastructure::InstanceCollection::getInstance<EntityManager>().killEntity(e1);

			auto& e2 = Infrastructure::InstanceCollection::getInstance<EntityManager>().createEntity();

			REQUIRE(e2.getId() == e1Id);

			auto& e3 = Infrastructure::InstanceCollection::getInstance<EntityManager>().createEntity();

			REQUIRE(e2.getId() < e3.getId());
		}

		TEST_CASE("Re used entities will not have their old components", "[EntityManager]") {
			Infrastructure::InstanceCollection::clear();
			Infrastructure::InstanceCollection::registerInstance<EntityManager>();

			auto& e1 = Infrastructure::InstanceCollection::getInstance<EntityManager>().createEntity();
			e1.addComponent(new TestComponent(e1.getId()));
			unsigned int e1Id = e1.getId();

			REQUIRE(e1.hasComponent<TestComponent>());

			Infrastructure::InstanceCollection::getInstance<EntityManager>().killEntity(e1Id);

			auto& e2 = Infrastructure::InstanceCollection::getInstance<EntityManager>().createEntity();

			REQUIRE(e1Id == e2.getId());
			REQUIRE_FALSE(e2.hasComponent<TestComponent>());
		}

		TEST_CASE("Marking an entity for removal will kill it when entity manager cleans up entities", "[EntityManager]") {
			Infrastructure::InstanceCollection::clear();
			Infrastructure::InstanceCollection::registerInstance<EntityManager>();

			auto& e1 = Infrastructure::InstanceCollection::getInstance<EntityManager>().createEntity();
			e1.addComponent(new TestComponent(e1.getId()));
			unsigned int e1Id = e1.getId();

			REQUIRE(Infrastructure::InstanceCollection::getInstance<EntityManager>().getEntity(e1Id).isAlive());
			e1.flagToBeRemoved();
			REQUIRE(Infrastructure::InstanceCollection::getInstance<EntityManager>().getEntity(e1Id).isAlive());
			Infrastructure::InstanceCollection::getInstance<EntityManager>().cleanupEntities();
			REQUIRE_FALSE(Infrastructure::InstanceCollection::getInstance<EntityManager>().getEntity(e1Id).isAlive());
		}

		TEST_CASE("When entity is killed the entity killed signal is invoked", "[EntityManager]") {
			Infrastructure::InstanceCollection::clear();
			Infrastructure::InstanceCollection::registerInstance<EntityManager>();

			auto& e1 = Infrastructure::InstanceCollection::getInstance<EntityManager>().createEntity();
			unsigned int killedEntityId;

			Infrastructure::InstanceCollection::getInstance<EntityManager>().entityKilled.registerCallback([&](unsigned int _entityId) {
				killedEntityId = _entityId;
			});

			Infrastructure::InstanceCollection::getInstance<EntityManager>().killEntity(e1);

			REQUIRE(killedEntityId == e1.getId());
		}
    }
}