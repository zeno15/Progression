#include <catch.hpp>

#include <System/Vector4.hpp>

namespace System {
	namespace Vector3Tests {

		TEST_CASE("Vector4 Test", "[Vector4]") {
			SECTION("Test default constructor") {
				System::Vector4<float> vec = System::Vector4<float>();

				REQUIRE(vec.x == 0.0f);
				REQUIRE(vec.y == 0.0f);
				REQUIRE(vec.z == 0.0f);
				REQUIRE(vec.w == 0.0f);
			}
			SECTION("Test non-default constructor") {
				float x = 1.0f;
				float y = 12.0f;
				float z = -12.8f;
				float w = 1.0f;
				System::Vector4<float> vec = System::Vector4<float>(x, y, z, w);

				REQUIRE(vec.x == x);
				REQUIRE(vec.y == y);
				REQUIRE(vec.z == z);
				REQUIRE(vec.w == w);
			}
			SECTION("Test copy constructor from same type") {
				float x = 1.2f;
				float y = 12.2f;
				float z = -12.8f;
				float w = 1.0f;
				System::Vector4<float> vec = System::Vector4<float>(x, y, z, w);
				System::Vector4<float> cpy = System::Vector4<float>(vec);

				REQUIRE(cpy == vec);
			}
			SECTION("Test copy constructor from different type") {
				int x = 12;
				int y = 453;
				int z = -18;
				int w = 1;
				System::Vector4<int> vec = System::Vector4<int>(x, y, z, w);
				System::Vector4<float> cpy = System::Vector4<float>(vec);

				REQUIRE(cpy == System::Vector4<float>(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z), static_cast<float>(w)));
			}
			SECTION("Test -(negate) operator") {
				float x = 12.3f;
				float y = -123.7f;
				float z = 88.1f;
				float w = 1.0f;

				System::Vector4<float> vec = System::Vector4<float>(x, y, z, w);
				vec = -vec;

				REQUIRE(vec == System::Vector4<float>(-x, -y, -z, w));
			}
			SECTION("TEST - operator") {
				float x = 12.6f;
				float y = 82.1f;
				float z = -12.8f;
				float w = 1.0f;

				System::Vector4<float> res = System::Vector4<float>(x, y, z, w) - System::Vector4<float>(x, y, z, w);

				REQUIRE(res == System::Vector4<float>(0.0f, 0.0f, 0.0f, w));
			}
			SECTION("Test -= operator") {
				float x = 12.6f;
				float y = 82.1f;
				float z = -8.1f;
				float w = 1.0f;

				System::Vector4<float> res = System::Vector4<float>(x, y, z, w);

				res -= System::Vector4<float>(x, y, z, w);

				REQUIRE(res == System::Vector4<float>(0.0f, 0.0f, 0.0f, w));
			}
			SECTION("Test + operator") {
				float x = 12.6f;
				float y = 82.1f;
				float z = -8.9f;
				float w = 1.0f;

				System::Vector4<float> res = System::Vector4<float>(x, y, z, w) + System::Vector4<float>(x, y, z, w);

				REQUIRE(res == System::Vector4<float>(2.0f * x, 2.0f * y, 2.0f * z, w));
			}
			SECTION("Test += operator")
			{
				float x = 12.6f;
				float y = 82.1f;
				float z = -8.5f;
				float w = 1.0f;

				System::Vector4<float> res = System::Vector4<float>(x, y, z, w);
				res += res;

				REQUIRE(res == System::Vector4<float>(2.0f * x, 2.0f * y, 2.0f * z, w));
			}
			SECTION("Test / operator") {
				float x = 123.75f;
				float y = 12.5f;
				float z = -23.4f;
				float w = 1.0f;
				float div = 7.4f;

				System::Vector4<float> vec = System::Vector4<float>(x, y, z, w);
				vec = vec / div;

				REQUIRE(vec == System::Vector4<float>(x / div, y / div, z / div, w));
			}
			SECTION("Test /= operator") {
				float x = 123.75f;
				float y = 12.5f;
				float z = -8.9f;
				float w = 1.0f;
				float div = 7.4f;

				System::Vector4<float> vec = System::Vector4<float>(x, y, z, w);
				vec /= div;

				REQUIRE(vec == System::Vector4<float>(x / div, y / div, z / div, w));
			}
			SECTION("Test * operator") {
				float x = 123.52f;
				float y = 7645.4f;
				float z = -123.6f;
				float w = 1.0f;
				float mul = 2.1f;

				System::Vector4<float> vec = System::Vector4<float>(x, y, z, w);
				vec = vec * mul;

				REQUIRE(vec == System::Vector4<float>(x * mul, y * mul, z * mul, w));


				vec = System::Vector4<float>(x, y, z, w);
				vec = mul * vec;

				REQUIRE(vec == System::Vector4<float>(x * mul, y * mul, z * mul, w));
			}
			SECTION("Test *= operator") {
				float x = 123.52f;
				float y = 7645.4f;
				float z = -764.4f;
				float w = 1.0f;
				float mul = 2.1f;

				System::Vector4<float> vec = System::Vector4<float>(x, y, z, w);
				vec *= mul;

				REQUIRE(vec == System::Vector4<float>(x * mul, y * mul, z* mul, w));
			}
			SECTION("Test == operator") {
				System::Vector4<float> vec1 = System::Vector4<float>(123.4f, 11.0f, -12.0f, 0.0f);
				System::Vector4<float> vec2 = System::Vector4<float>(13.4f, 1121.0f, -64.4f, 0.0f);

				REQUIRE_FALSE(vec1 == vec2);

				vec2 = vec1;
				REQUIRE(vec1 == vec2);
			}
			SECTION("Test != operator") {
				System::Vector4<float> vec1 = System::Vector4<float>(123.4f, 11.0f, -12.0f, 0.0f);
				System::Vector4<float> vec2 = System::Vector4<float>(13.4f, 1121.0f, -64.4f, 0.0f);

				REQUIRE(vec1 != vec2);

				vec2 = vec1;
				REQUIRE_FALSE(vec1 != vec2);
			}
		}
	}
}