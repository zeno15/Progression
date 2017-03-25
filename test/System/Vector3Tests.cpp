#include <catch.hpp>

#include <System/Vector3.hpp>

namespace System {
	namespace Vector3Tests {


		TEST_CASE("Vector3 Test", "[Vector3]") {
			SECTION("Test default constructor") {
				System::Vector3<float> vec = System::Vector3<float>();

				REQUIRE(vec.x == 0.0f);
				REQUIRE(vec.y == 0.0f);
				REQUIRE(vec.z == 0.0f);
			}
			SECTION("Test non-default constructor") {
				float x = 1.0f;
				float y = 12.0f;
				float z = -12.8f;
				System::Vector3<float> vec = System::Vector3<float>(x, y, z);

				REQUIRE(vec.x == x);
				REQUIRE(vec.y == y);
				REQUIRE(vec.z == z);
			}
			SECTION("Test copy constructor from same type") {
				float x = 1.2f;
				float y = 12.2f;
				float z = -12.8f;
				System::Vector3<float> vec = System::Vector3<float>(x, y, z);
				System::Vector3<float> cpy = System::Vector3<float>(vec);

				REQUIRE(cpy == vec);
			}
			SECTION("Test copy constructor from different type") {
				int x = 12;
				int y = 453;
				int z = -18;
				System::Vector3<int> vec = System::Vector3<int>(x, y, z);
				System::Vector3<float> cpy = System::Vector3<float>(vec);

				REQUIRE(cpy == System::Vector3<float>(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z)));
			}
			SECTION("Test -(negate) operator") {
				float x = 12.3f;
				float y = -123.7f;
				float z = 88.1f;

				System::Vector3<float> vec = System::Vector3<float>(x, y, z);
				vec = -vec;

				REQUIRE(vec == System::Vector3<float>(-x, -y, -z));
			}
			SECTION("TEST - operator") {
				float x = 12.6f;
				float y = 82.1f;
				float z = -12.8f;

				System::Vector3<float> res = System::Vector3<float>(x, y, z) - System::Vector3<float>(x, y, z);

				REQUIRE(res == System::Vector3<float>());
			}
			SECTION("Test -= operator") {
				float x = 12.6f;
				float y = 82.1f;
				float z = -8.1f;

				System::Vector3<float> res = System::Vector3<float>(x, y, z);

				res -= System::Vector3<float>(x, y, z);

				REQUIRE(res == System::Vector3<float>());
			}
			SECTION("Test + operator")
			{
				float x = 12.6f;
				float y = 82.1f;
				float z = -8.9f;

				System::Vector3<float> res = System::Vector3<float>(x, y, z) + System::Vector3<float>(x, y, z);

				REQUIRE(res == System::Vector3<float>(2.0f * x, 2.0f * y, 2.0f * z));
			}
			SECTION("Test += operator") {
				float x = 12.6f;
				float y = 82.1f;
				float z = -8.5f;

				System::Vector3<float> res = System::Vector3<float>(x, y, z);
				res += res;

				REQUIRE(res == System::Vector3<float>(2.0f * x, 2.0f * y, 2.0f * z));
			}
			SECTION("Test / operator") {
				float x = 123.75f;
				float y = 12.5f;
				float z = -23.4f;
				float div = 7.4f;

				System::Vector3<float> vec = System::Vector3<float>(x, y, z);
				vec = vec / div;

				REQUIRE(vec == System::Vector3<float>(x / div, y / div, z / div));
			}
			SECTION("Test /= operator")
			{
				float x = 123.75f;
				float y = 12.5f;
				float z = -8.9f;
				float div = 7.4f;

				System::Vector3<float> vec = System::Vector3<float>(x, y, z);
				vec /= div;

				REQUIRE(vec == System::Vector3<float>(x / div, y / div, z / div));
			}
			SECTION("Test * operator") {
				float x = 123.52f;
				float y = 7645.4f;
				float z = -123.6f;
				float mul = 2.1f;

				System::Vector3<float> vec = System::Vector3<float>(x, y, z);
				vec = vec * mul;

				REQUIRE(vec == System::Vector3<float>(x * mul, y * mul, z * mul));


				vec = System::Vector3<float>(x, y, z);
				vec = mul * vec;

				REQUIRE(vec == System::Vector3<float>(x * mul, y * mul, z * mul));
			}
			SECTION("Test *= operator") {
				float x = 123.52f;
				float y = 7645.4f;
				float z = -764.4f;
				float mul = 2.1f;

				System::Vector3<float> vec = System::Vector3<float>(x, y, z);
				vec *= mul;

				REQUIRE(vec == System::Vector3<float>(x * mul, y * mul, z* mul));
			}
			SECTION("Test == operator") {
				System::Vector3<float> vec1 = System::Vector3<float>(123.4f, 11.0f, -12.0f);
				System::Vector3<float> vec2 = System::Vector3<float>(13.4f, 1121.0f, -64.4f);

				REQUIRE_FALSE(vec1 == vec2);

				vec2 = vec1;
				REQUIRE(vec1 == vec2);
			}
			SECTION("Test != operator") {
				System::Vector3<float> vec1 = System::Vector3<float>(123.4f, 11.0f, -12.0f);
				System::Vector3<float> vec2 = System::Vector3<float>(13.4f, 1121.0f, -64.4f);

				REQUIRE(vec1 != vec2);

				vec2 = vec1;
				REQUIRE_FALSE(vec1 != vec2);
			}
		}
	}
}