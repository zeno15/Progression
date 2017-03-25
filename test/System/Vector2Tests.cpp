#include <catch.hpp>

#include <System/Vector2.hpp>

namespace System {
	namespace Vector2Tests {

		TEST_CASE("Vector2 Test", "[Vector2]") {
			SECTION("Test default constructor") {
				Vector2<float> vec = Vector2<float>();

				REQUIRE(vec.x == 0.0f);
				REQUIRE(vec.y == 0.0f);
			}

			SECTION("Test non-default constructor") {
				float x = 1.0f;
				float y = 12.0f;
				Vector2<float> vec = Vector2<float>(x, y);

				REQUIRE(vec.x == x);
				REQUIRE(vec.y == y);
			}

			SECTION("Test copy constructor from same type") {
				float x = 1.2f;
				float y = 12.2f;
				Vector2<float> vec = Vector2<float>(x, y);
				Vector2<float> cpy = Vector2<float>(vec);

				REQUIRE(cpy == vec);
			}

			SECTION("Test copy constructor from different type") {
				int x = 12;
				int y = 453;
				Vector2<int> vec = Vector2<int>(x, y);
				Vector2<float> cpy = Vector2<float>(vec);

				REQUIRE(cpy.x == static_cast<float>(x));
				REQUIRE(cpy.y == static_cast<float>(y));
			}

			SECTION("Test -(negate) operator") {
				float x = 12.3f;
				float y = -123.7f;

				Vector2<float> vec = Vector2<float>(x, y);
				vec = -vec;

				REQUIRE(vec.x == -x);
				REQUIRE(vec.y == -y);
			}

			SECTION("TEST - operator") {
				float x = 12.6f;
				float y = 82.1f;

				Vector2<float> res = Vector2<float>(x, y) - Vector2<float>(x, y);

				REQUIRE(res == Vector2<float>(0.0f, 0.0f));
			}

			SECTION("Test -= operator") {
				float x = 12.6f;
				float y = 82.1f;

				Vector2<float> res = Vector2<float>(x, y);

				res -= Vector2<float>(x, y);

				REQUIRE(res == Vector2<float>(0.0f, 0.0f));
			}

			SECTION("Test + operator") {
				float x = 12.6f;
				float y = 82.1f;

				Vector2<float> res = Vector2<float>(x, y) + Vector2<float>(x, y);

				REQUIRE(res == Vector2<float>(2.0f * x, 2.0f * y));
			}

			SECTION("Test += operator") {
				float x = 12.6f;
				float y = 82.1f;

				Vector2<float> res = Vector2<float>(x, y);
				res += res;

				REQUIRE(res == Vector2<float>(2.0f * x, 2.0f * y));
			}

			SECTION("Test / operator") {
				float x = 123.75f;
				float y = 12.5f;
				float div = 7.4f;

				Vector2<float> vec = Vector2<float>(x, y);
				vec = vec / div;

				REQUIRE(vec == Vector2<float>(x / div, y / div));
			}

			SECTION("Test /= operator") {
				float x = 123.75f;
				float y = 12.5f;
				float div = 7.4f;

				Vector2<float> vec = Vector2<float>(x, y);
				vec /= div;

				REQUIRE(vec == Vector2<float>(x / div, y / div));
			}

			SECTION("Test * operator") {
				float x = 123.52f;
				float y = 7645.4f;
				float mul = 2.1f;

				Vector2<float> vec = Vector2<float>(x, y);
				vec = vec * mul;

				REQUIRE(vec == Vector2<float>(x * mul, y * mul));


				vec = Vector2<float>(x, y);
				vec = mul * vec;

				REQUIRE(vec == Vector2<float>(x * mul, y * mul));
			}

			SECTION("Test *= operator") {
				float x = 123.52f;
				float y = 7645.4f;
				float mul = 2.1f;

				Vector2<float> vec = Vector2<float>(x, y);
				vec *= mul;

				REQUIRE(vec == Vector2<float>(x * mul, y * mul));
			}

			SECTION("Test == operator") {
				Vector2<float> vec1 = Vector2<float>(123.4f, 11.0f);
				Vector2<float> vec2 = Vector2<float>(13.4f, 1121.0f);

				REQUIRE_FALSE(vec1 == vec2);

				vec2 = vec1;
				REQUIRE(vec1 == vec2);
			}

			SECTION("Test != operator") {
				Vector2<float> vec1 = Vector2<float>(123.4f, 11.0f);
				Vector2<float> vec2 = Vector2<float>(13.4f, 1121.0f);

				REQUIRE(vec1 != vec2);

				vec2 = vec1;
				REQUIRE_FALSE(vec1 != vec2);
			}
		}
	}
}