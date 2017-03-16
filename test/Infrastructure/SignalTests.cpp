#include <catch.hpp>

#include <Infrastructure/Signal.hpp>


namespace Infrastructure {
	namespace SignalTests {

		void testCallback(int _callbackValue) {

		}


		class TestCallbackClass {
		public:
			TestCallbackClass(void) : m_NonStaticValue(0) {}
			void testCallback(int _value) {
				m_NonStaticValue += _value;
			}

			static void staticTestCallback(int _value) {
				m_StaticValue += _value;
			}

			int m_NonStaticValue;
			static int m_StaticValue;
		};

		int TestCallbackClass::m_StaticValue = 0;

		TEST_CASE("Signal with single callback is executed", "[Signal]") {
			int currentValue = 0;
			int callbackValue = 5;

			Signal<int> intCallbackSignal = Signal<int>();
			
			intCallbackSignal.registerCallback(
				[&](int _value) {
					currentValue += _value;
				});

			REQUIRE(intCallbackSignal.getNumberOfCallbacks() == 1);

			intCallbackSignal.invoke(callbackValue);

			REQUIRE(currentValue == callbackValue);
		}

		TEST_CASE("Signal with multiple callbacks are all executed", "[Signal]") {
			int currentValue = 0;
			int callbackValue = 5;
			int iterations = 12;

			Signal<int> intCallbackSignal = Signal<int>();

			for (int i = 0; i < iterations; i += 1) {
				intCallbackSignal.registerCallback(
					[&](int _value) {
					currentValue += _value;
				});
			}


			REQUIRE(intCallbackSignal.getNumberOfCallbacks() == static_cast<unsigned int>(iterations));

			intCallbackSignal.invoke(callbackValue);

			REQUIRE(currentValue == callbackValue * iterations);
		}

		TEST_CASE("Signal registration gives id, can remove callback with it and clear", "[Signal]") {
			int currentValue = 0;
			int callbackValue = 5;
			int iterations = 12;
			int callbackId = 0;
			int callbackIndexToRemove = 3;

			REQUIRE(iterations > callbackIndexToRemove);

			Signal<int> intCallbackSignal = Signal<int>();

			for (int i = 0; i < iterations; i += 1) {
				int id = intCallbackSignal.registerCallback(
					[&](int _value) {
					currentValue += _value;
				});

				if (i == callbackIndexToRemove) {
					callbackId = id;
				}
			}


			REQUIRE(intCallbackSignal.getNumberOfCallbacks() == static_cast<unsigned int>(iterations));

			intCallbackSignal.unregisterCallback(callbackId);

			REQUIRE(intCallbackSignal.getNumberOfCallbacks() == static_cast<unsigned int>(iterations - 1));

			intCallbackSignal.invoke(callbackValue);

			REQUIRE(currentValue == callbackValue * (iterations - 1));

			intCallbackSignal.clearCallbacks();

			REQUIRE(0u == intCallbackSignal.getNumberOfCallbacks());
		}

		TEST_CASE("Registering a non lambda method works", "[Signal]") {
			Signal<int> intCallbackSignal = Signal<int>();
			int callbackValue = 5;

			intCallbackSignal.registerCallback(std::function<void(int)>(testCallback));

			intCallbackSignal.invoke(callbackValue);
			
		}

		TEST_CASE("A static class method works", "[Signal]") {
			TestCallbackClass::m_StaticValue = 0;
			Signal<int> intCallbackSignal = Signal<int>();
			int callbackValue = 5;

			std::function<void(int)> callback = &TestCallbackClass::staticTestCallback;

			intCallbackSignal.registerCallback(std::function<void(int)>(callback));

			REQUIRE(TestCallbackClass::m_StaticValue == 0);
			intCallbackSignal.invoke(callbackValue);
			REQUIRE(TestCallbackClass::m_StaticValue == callbackValue);
		}

		TEST_CASE("A non static class method works", "[Signal]") {
			TestCallbackClass classInstance = TestCallbackClass();
			Signal<int> intCallbackSignal = Signal<int>();
			int callbackValue = 5;

			std::function<void(int)> callback = std::bind(&TestCallbackClass::testCallback, &classInstance, std::placeholders::_1);

			intCallbackSignal.registerCallback(std::function<void(int)>(callback));

			REQUIRE(classInstance.m_NonStaticValue == 0);
			intCallbackSignal.invoke(callbackValue);
			REQUIRE(classInstance.m_NonStaticValue == callbackValue);

		}
	}
}