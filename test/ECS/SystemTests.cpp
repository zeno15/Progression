#include <catch.hpp>

#include <ECS/System.hpp>
#include <ECS/Component.hpp>

#include <utility>

namespace ECS {
    namespace SystemTests {
    	class TestComponent : public Component {
		public:
			TestComponent(unsigned int _entityId) : Component(_entityId) {}
    	};
    	class TestComponentSystem : public System<TestComponent> {

    	};
    	class NoComponentSystem : public System<> {

    	};
        TEST_CASE("Can construct system without component limitation", "[System]") {
			Infrastructure::InstanceCollection::clear();
			Infrastructure::InstanceCollection::registerInstance<EntityManager>();

        	auto noComponentSystem = NoComponentSystem();
        }
        TEST_CASE("Can construct system with component limitation", "[System]") {
			Infrastructure::InstanceCollection::clear();
			Infrastructure::InstanceCollection::registerInstance<EntityManager>();

        	auto testComponentSystem = TestComponentSystem();
        }

		TEST_CASE("Killing an entity in the entity manager removes it from a system", "[System]") {
			Infrastructure::InstanceCollection::clear();
			Infrastructure::InstanceCollection::registerInstance<EntityManager>();

			auto noComponentSystem = NoComponentSystem();

			auto& e = Infrastructure::InstanceCollection::getInstance<EntityManager>().createEntity();

			noComponentSystem.addEntity(e);

			REQUIRE(noComponentSystem.containsEntity(e.getId()));

			Infrastructure::InstanceCollection::getInstance<EntityManager>().killEntity(e.getId());

			REQUIRE_FALSE(noComponentSystem.containsEntity(e.getId()));
		}
    }
}