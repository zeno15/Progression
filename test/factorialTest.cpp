#include <catch.hpp>

#include <Progression/Factorial.hpp>

namespace cppbase {
    namespace tests {
        TEST_CASE("Test factorial function", "[Factorial]") {
            REQUIRE_THROWS(computeFactorial(-5));
            REQUIRE(computeFactorial(0) == 1);
            REQUIRE(computeFactorial(1) == 1);
            REQUIRE(computeFactorial(2) == 2);
            REQUIRE(computeFactorial(5) == 1120);
        }    
    }
}

