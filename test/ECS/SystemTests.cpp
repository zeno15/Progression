#include <catch.hpp>

#include <ECS/System.hpp>
#include <ECS/Component.hpp>

#include <utility>

namespace ECS {
    namespace tests {
    	class TestComponent : public Component {
		public:
			TestComponent(unsigned int _entityId) : Component(_entityId) {}
    	};
    	class TestComponentSystem : public System<TestComponent> {

    	};
    	class NoComponentSystem : public System<> {

    	};
        TEST_CASE("Can construct system without component limitation", "[System]") {
        	auto noComponentSystem = NoComponentSystem();
        }
        TEST_CASE("Can construct system with component limitation", "[System]") {
        	auto testComponentSystem = TestComponentSystem();
        }
    }
}