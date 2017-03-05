#include <catch.hpp>

#include <ECS/Entity.hpp>
#include <ECS/Component.hpp>

#include <utility>

namespace ECS {
    namespace tests {
		class TestComponent1 : public Component {
		public:
			TestComponent1(unsigned int _entityId) : Component(_entityId) {}
		};
		class TestComponent2 : public Component {
		public:
			TestComponent2(unsigned int _entityId) : Component(_entityId) {}
		};
		class TestComponent3 : public Component {
		public:
			TestComponent3(unsigned int _entityId) : Component(_entityId) {}
		};


        TEST_CASE("Test default constructor applies id", "[Entity]") {
        	unsigned int id = 552;

        	auto entity = ECS::Entity(id);

        	REQUIRE(entity.getId() == id);
        }    

        TEST_CASE("Test copy constructor applies id", "[Entity]") {
        	unsigned int id = 552;

        	auto entity1 = ECS::Entity(id);
        	auto entity2 = std::move(entity1);

        	REQUIRE(entity1.getId() == id);
        	REQUIRE(entity2.getId() == id);
        }

        TEST_CASE("Entity with no components says it doesnt have each test component", "[Entity]") {
        	unsigned int id = 552;

        	auto entity = ECS::Entity(id);

        	REQUIRE_FALSE(entity.hasComponent<TestComponent1>());
        	REQUIRE_FALSE(entity.hasComponent<TestComponent2>());
        	REQUIRE_FALSE(entity.hasComponent<TestComponent3>());
        }

        TEST_CASE("Entity with no components says it doesnt have any with multi component type", "[Entity") {
			unsigned int id = 552;

        	auto entity = ECS::Entity(id);
    		bool result = entity.hasComponents<TestComponent1, TestComponent2, TestComponent3>();
    		REQUIRE_FALSE(result);
        }

        TEST_CASE("Entity with single component says it has it", "[Entity]") {
        	unsigned int id = 552;

        	auto entity = ECS::Entity(id);
        	entity.addComponent(new TestComponent1(id));

        	REQUIRE(entity.hasComponent<TestComponent1>());
        }

        TEST_CASE("Entity with all components says it has them", "[Entity]") {
        	unsigned int id = 552;

        	auto entity = ECS::Entity(id);
        	entity.addComponent(new TestComponent1(id));
        	entity.addComponent(new TestComponent2(id));
        	entity.addComponent(new TestComponent3(id));

    		bool result = entity.hasComponents<TestComponent1, TestComponent2, TestComponent3>();

        	REQUIRE(result);
        }
    }
}

