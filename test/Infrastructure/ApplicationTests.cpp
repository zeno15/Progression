#include <catch.hpp>

#include <Infrastructure/Application.hpp>
#include <Infrastructure/InstanceCollection.hpp>


namespace Infrastructure {
	namespace ApplicationTests {
		/*TEST_CASE("Application starts off not running", "[Application]") {
			InstanceCollection::clear();
			InstanceCollection::registerInstance<Application>();

			REQUIRE_FALSE(InstanceCollection::getInstance<Application>().isRunning());
		}*/
	}
}