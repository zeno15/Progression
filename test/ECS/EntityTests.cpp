#include <catch.hpp>

#include <ECS/Entity.hpp>

#include <utility>

namespace ECS {
    namespace tests {
        TEST_CASE("Test default constructor applies id", "[Entity]") {
        	unsigned int id = 552;

        	auto entity = ECS::Entity(id);

        	REQUIRE(entity.getId() == id);
        }    

        TEST_CASE("Test copy constructor applies id", "[Entity]") {
        	unsigned int id = 552;

        	auto entity1 = ECS::Entity(id);
        	auto& entity2 = std::move(entity1);

        	REQUIRE(entity1.getId() == id);
        	REQUIRE(entity2.getId() == id);
        }
    }
}

