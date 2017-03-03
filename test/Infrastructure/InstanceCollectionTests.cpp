#include <catch.hpp>

#include <Infrastructure/InstanceCollection.hpp>

namespace Infrastructure {
    namespace tests {
    	class TestManager : public Manager {
    	public:
    		static const std::string Name;

    		void setTestValue1(unsigned int _value1) {
    			m_TestValue1 = _value1;
    		}
    		unsigned int getTestValue1(void) const {
    			return m_TestValue1;
    		}

    	private:
    		unsigned int m_TestValue1;
    	};

    	const std::string TestManager::Name = "TestManager";

    	TEST_CASE("", "[InstanceCollection]") {
    		InstanceCollection::registerInstance<TestManager>();

    		unsigned int value = 123;

    		InstanceCollection::getInstance<TestManager>().setTestValue1(value);

    		REQUIRE(value == InstanceCollection::getInstance<TestManager>().getTestValue1());
    	}
	}
}