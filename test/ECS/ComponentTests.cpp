#include <catch.hpp>

#include <ECS/Component.hpp>

#include <utility>


namespace tests {
    TEST_CASE("Test default constructor applies entity id", "[Component]") {
    	unsigned int id = 552;

    	auto& component = ECS::Component(id);

    	REQUIRE(component.getEntityId() == id);
    } 
}
