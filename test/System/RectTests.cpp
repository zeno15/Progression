#include <catch.hpp>

#include <System/Vector2.hpp>
#include <System/Rect.hpp>

namespace System {
	namespace RectTests {
		TEST_CASE("Rect Test", "[Rect]") {
			SECTION("Test default constructor") {
				System::Rect<int> rect = System::Rect<int>();

				REQUIRE((rect.left == 0 &&
					rect.bot == 0 &&
					rect.width == 0 &&
					rect.height == 0));
			}
			SECTION("Test non-default constructor") {
				int l = 1;
				int b = 2;
				int w = 5;
				int h = 6;

				System::Rect<int> rect = System::Rect<int>(l, b, w, h);

				REQUIRE((rect.left == l 	&&
					rect.bot == b 	&&
					rect.width == w 	&&
					rect.height == h));
			}
			SECTION("Test copy constructor") {
				int l = 1;
				int b = 2;
				int w = 5;
				int h = 6;

				System::Rect<int> recti = System::Rect<int>(l, b, w, h);

				System::Rect<float> rectf = System::Rect<float>(recti);

				REQUIRE((rectf.left == static_cast<float>(recti.left) &&
					rectf.bot == static_cast<float>(recti.bot) &&
					rectf.width == static_cast<float>(recti.width) &&
					rectf.height == static_cast<float>(recti.height)));
			}
			SECTION("Test contains") {
				System::Rect<int> rect = System::Rect<int>(0, 0, 10, 10);

				REQUIRE(rect.contains(5, 5));
				REQUIRE(rect.contains(System::Vector2<int>(5, 5)));

				REQUIRE_FALSE(rect.contains(-5, 15));
				REQUIRE_FALSE(rect.contains(System::Vector2<int>(15, -5)));
			}
			SECTION("Test intersects") {
				System::Rect<int> rect1 = System::Rect<int>(0, 0, 10, 10);
				System::Rect<int> rect2 = rect1;

				System::Rect<int> result = System::Rect<int>();

				REQUIRE(rect1.intersects(rect2, result));

				REQUIRE(result == System::Rect<int>(0, 0, 10, 10));

				rect2 = System::Rect<int>(10, 10, 10, 10);

				REQUIRE_FALSE(rect1.intersects(rect2, result));
			}
			SECTION("Test == operator") {
				System::Rect<int> rect = System::Rect<int>(1, 2, 3, 4);

				REQUIRE(rect == System::Rect<int>(1, 2, 3, 4));

				REQUIRE_FALSE(rect == System::Rect<int>(2, 3, 4, 5));
			}
			SECTION("Test != operator") {
				System::Rect<int> rect = System::Rect<int>(1, 2, 3, 4);

				REQUIRE_FALSE(rect != System::Rect<int>(1, 2, 3, 4));

				REQUIRE(rect != System::Rect<int>(2, 3, 4, 5));
			}
		}
	}
}