#include <catch.hpp>

#include <System/Time.hpp>

namespace System {
	namespace TimeTests {

		TEST_CASE("Time Test", "[Time]") {
			SECTION("Test time default constructor gives 0 initial value") {
				System::Time t = System::Time();

				REQUIRE(t.asMicroseconds() == 0);
			}
			SECTION("Test non default seconds constructor works as REQUIREed") {
				System::Time t = System::Time::seconds(1.0f);

				REQUIRE(t.asSeconds() == 1.0f);
				REQUIRE(t.asMilliseconds() == 1000);
				REQUIRE(t.asMicroseconds() == 1000000);
			}
			SECTION("Test non default milliseconds constructor works as REQUIREed") {
				System::Time t = System::Time::milliseconds(1000);

				REQUIRE(t.asSeconds() == 1.0f);
				REQUIRE(t.asMilliseconds() == 1000);
				REQUIRE(t.asMicroseconds() == 1000000);
			}
			SECTION("Test non default microseconds constructor works as REQUIREed") {
				System::Time t = System::Time::microseconds(1000000);

				REQUIRE(t.asSeconds() == 1.0f);
				REQUIRE(t.asMilliseconds() == 1000);
				REQUIRE(t.asMicroseconds() == 1000000);
			}
			SECTION("Test == operator") {
				System::Time t1 = System::Time::microseconds(1);
				System::Time t2 = System::Time::microseconds(1);
				REQUIRE(t1 == t2);

				t1 = System::Time::microseconds(1000);
				t2 = System::Time::milliseconds(1);
				REQUIRE(t1 == t2);

				t1 = System::Time::seconds(12.0f);
				REQUIRE_FALSE(t1 == t2);
			}
			SECTION("Test != operator") {
				System::Time t1 = System::Time::microseconds(1);
				System::Time t2 = System::Time::microseconds(1);
				REQUIRE_FALSE(t1 != t2);

				t1 = System::Time::seconds(10.0f);
				REQUIRE(t1 != t2);
			}
			SECTION("Test > operator") {
				System::Time t1 = System::Time::microseconds(1);
				System::Time t2 = System::Time::microseconds(1);
				REQUIRE_FALSE(t1 > t2);

				t1 = System::Time::microseconds(100);
				REQUIRE(t1 > t2);
				REQUIRE_FALSE(t2 > t1);
			}
			SECTION("Test >= operator")
			{
				System::Time t1 = System::Time::microseconds(1);
				System::Time t2 = System::Time::microseconds(1);
				REQUIRE(t1 >= t2);
				REQUIRE(t2 >= t1);

				t1 = System::Time::microseconds(10);
				REQUIRE(t1 >= t2);
				REQUIRE_FALSE(t2 >= t1);
			}
			SECTION("Test < operator") {
				System::Time t1 = System::Time::microseconds(1);
				System::Time t2 = System::Time::microseconds(1);
				REQUIRE_FALSE(t1 < t2);

				t1 = System::Time::microseconds(10);
				REQUIRE(t2 < t1);
				REQUIRE_FALSE(t1 < t2);
			}
			SECTION("Test <= operator") {
				System::Time t1 = System::Time::microseconds(1);
				System::Time t2 = System::Time::microseconds(1);
				REQUIRE(t1 <= t2);
				REQUIRE(t2 <= t1);

				t1 = System::Time::microseconds(10);
				REQUIRE(t2 <= t1);
				REQUIRE_FALSE(t1 <= t2);
			}
			SECTION("Test -(negate) operator") {
				System::Time t1 = System::Time::microseconds(1);
				REQUIRE(t1.asMicroseconds() == 1);

				t1 = -t1;
				REQUIRE(t1.asMicroseconds() == -1);
			}
			SECTION("Test - operator") {
				System::Time t1 = System::Time::microseconds(1);
				System::Time t2 = System::Time::microseconds(1);
				System::Time res = t1 - t2;
				REQUIRE(res == System::Time::microseconds(0));

				t2 = System::Time::microseconds(10);
				res = t1 - t2;
				REQUIRE(res == System::Time::microseconds(-9));
			}
			SECTION("Test -= operator") {
				System::Time t1 = System::Time::microseconds(1);
				System::Time t2 = System::Time::microseconds(1);
				t1 -= t2;
				REQUIRE(t1.asMicroseconds() == 0);

				t1 -= t2;
				REQUIRE(t1.asMicroseconds() == -1);
			}
			SECTION("Test + operator") {
				System::Time t1 = System::Time::microseconds(1);
				System::Time t2 = System::Time::microseconds(1);
				System::Time res = t1 + t2;
				REQUIRE(res == System::Time::microseconds(2));

				t1 = System::Time::microseconds(-5);
				res = t1 + t2;
				REQUIRE(res == System::Time::microseconds(-4));
			}
			SECTION("Test += operator") {
				System::Time t1 = System::Time::microseconds(1);
				System::Time t2 = System::Time::microseconds(1);
				t1 += t2;
				REQUIRE(t1 == System::Time::microseconds(2));

				t2 = System::Time::microseconds(-5);
				t1 += t2;
				REQUIRE(t1 == System::Time::microseconds(-3));
			}
			SECTION("Test / operator") {
				System::Time t1 = System::Time::seconds(1.0f);
				System::Time t2 = System::Time::seconds(0.5f);
				float tf = 0.1f;
				long long tll = 1000000;


				REQUIRE((t1 / t2) == 2.0f);

				REQUIRE((t1 / tf) == System::Time::seconds(10.0f));

				REQUIRE((t1 / tll) == System::Time::microseconds(1));
			}
			SECTION("Test /= operator") {
				System::Time t1 = System::Time::seconds(100);
				System::Time t2 = System::Time::microseconds(100);

				t1 /= 4.0f;
				REQUIRE(t1 == System::Time::seconds(25.0f));

				t2 /= 20ll;
				REQUIRE(t2 == System::Time::microseconds(5));
			}
			SECTION("Test * operator") {
				System::Time t1 = System::Time::seconds(10);
				System::Time t2 = System::Time::microseconds(10);

				System::Time res = t1 * 3.0f;
				REQUIRE(res == System::Time::seconds(30.0f));

				res = t2 * 3ll;
				REQUIRE(res == System::Time::microseconds(30));

				res = 3.0f * t1;
				REQUIRE(res == System::Time::seconds(30.0f));

				res = 3ll * t2;
				REQUIRE(res == System::Time::microseconds(30));
			}
			SECTION("Test *= operator") {
				System::Time t1 = System::Time::seconds(1);
				System::Time t2 = System::Time::microseconds(1);

				t1 *= 100.0f;
				REQUIRE(t1 == System::Time::seconds(100.0f));

				t2 *= 1023ll;
				REQUIRE(t2 == System::Time::microseconds(1023));
			}
			SECTION("Test % operator") {
				System::Time t1 = System::Time::microseconds(10);
				System::Time t2 = System::Time::microseconds(4);

				System::Time res = t1 % t2;
				REQUIRE(res == System::Time::microseconds(2));

				t2 = System::Time::microseconds(5);
				res = t1 % t2;
				REQUIRE(res == System::Time::microseconds(0));
			}
			SECTION("Test %= operator") {
				System::Time t1 = System::Time::microseconds(10);
				System::Time t2 = System::Time::microseconds(10);

				t1 %= t2;
				REQUIRE(t1 == System::Time::microseconds(0));

				t1 = System::Time::microseconds(10);
				t2 = System::Time::microseconds(4);
				t1 %= t2;
				REQUIRE(t1 == System::Time::microseconds(2));
			}
		}
	}
}
