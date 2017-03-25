#include <catch.hpp>

#include <Graphics/Colour.hpp>

namespace System {
	namespace ColourTests {
		TEST_CASE("Colour Test", "[Colour]") {
			SECTION("Test default constructor") {
				Graphics::Colour col = Graphics::Colour();

				REQUIRE((col.r == 0.0f &&
					col.g == 0.0f &&
					col.b == 0.0f &&
					col.a == 1.0f));
			}
			SECTION("Test non-default constructor") {
				float r = 0.2f;
				float g = 0.4f;
				float b = 0.6f;
				float a = 0.8f;
				Graphics::Colour col = Graphics::Colour(r, g, b, a);

				REQUIRE((col.r == r &&
					col.g == g &&
					col.b == b &&
					col.a == a));
			}
			SECTION("Test Black Graphics::Colour") {
				Graphics::Colour col = Graphics::Colour::Black;

				REQUIRE(col == Graphics::Colour(0.0f, 0.0f, 0.0f, 1.0f));
			}
			SECTION("Test White Graphics::Colour") {
				Graphics::Colour col = Graphics::Colour::White;

				REQUIRE(col == Graphics::Colour(1.0f, 1.0f, 1.0f));
			}
			SECTION("Test Red Graphics::Colour") {
				Graphics::Colour col = Graphics::Colour::Red;

				REQUIRE(col == Graphics::Colour(1.0f, 0.0f, 0.0f));
			}
			SECTION("Test Green Graphics::Colour") {
				Graphics::Colour col = Graphics::Colour::Green;

				REQUIRE(col == Graphics::Colour(0.0f, 1.0f, 0.0f));
			}
			SECTION("Test Blue Graphics::Colour") {
				Graphics::Colour col = Graphics::Colour::Blue;

				REQUIRE(col == Graphics::Colour(0.0f, 0.0f, 1.0f));
			}
			SECTION("Test Yellow Graphics::Colour") {
				Graphics::Colour col = Graphics::Colour::Yellow;

				REQUIRE(col == Graphics::Colour(1.0f, 1.0f, 0.0f));
			}
			SECTION("Test Magenta Graphics::Colour") {
				Graphics::Colour col = Graphics::Colour::Magenta;

				REQUIRE(col == Graphics::Colour(1.0f, 0.0f, 1.0f));
			}
			SECTION("Test Cyan Graphics::Colour") {
				Graphics::Colour col = Graphics::Colour::Cyan;

				REQUIRE(col == Graphics::Colour(0.0f, 1.0f, 1.0f));
			}
			SECTION("Test Transparent Graphics::Colour") {
				Graphics::Colour col = Graphics::Colour::Transparent;

				REQUIRE(col == Graphics::Colour(0.0f, 0.0f, 0.0f, 0.0f));
			}
			SECTION("Test == operator") {
				float r = 0.2f;
				float g = 0.4f;
				float b = 0.6f;
				float a = 0.8f;
				Graphics::Colour col = Graphics::Colour(r, g, b, a);

				REQUIRE(col == Graphics::Colour(r, g, b, a));

				REQUIRE_FALSE(col == Graphics::Colour(a, b, g, r));
			}
			SECTION("Test != operator") {
				float r = 0.2f;
				float g = 0.4f;
				float b = 0.6f;
				float a = 0.8f;
				Graphics::Colour col = Graphics::Colour(r, g, b, a);

				REQUIRE_FALSE(col != Graphics::Colour(r, g, b, a));

				REQUIRE(col != Graphics::Colour(a, b, g, r));
			}
			SECTION("Test + operator") {
				Graphics::Colour red = Graphics::Colour::Red;
				Graphics::Colour green = Graphics::Colour::Green;

				REQUIRE((red + green) == Graphics::Colour::Yellow);

				REQUIRE((red + red) == Graphics::Colour::Red);
			}
			SECTION("Test += operator") {
				Graphics::Colour col = Graphics::Colour::Red;

				col += Graphics::Colour::Green;

				REQUIRE(col == Graphics::Colour::Yellow);
			}
			SECTION("Test - operator") {
				Graphics::Colour yellow = Graphics::Colour::Yellow;
				Graphics::Colour red = Graphics::Colour::Red;

				REQUIRE((yellow - red) == Graphics::Colour::Green);

				REQUIRE((yellow - yellow) == Graphics::Colour::Black);
			}
			SECTION("Test -= operator") {
				Graphics::Colour col = Graphics::Colour::Red;

				col -= Graphics::Colour::Red;

				REQUIRE(col == Graphics::Colour::Black);
			}
			SECTION("Test * operator (float)") {
				float r = 1.0f;
				float g = 1.0f;
				float b = 1.0f;

				float val = 0.5f;

				Graphics::Colour col = Graphics::Colour(r, g, b);

				REQUIRE((col * val) == Graphics::Colour(r * val, g * val, b * val));
			}
			SECTION("Test * operator (Colour)") {
				Graphics::Colour red = Graphics::Colour::Red;
				Graphics::Colour white = Graphics::Colour::White;

				REQUIRE((red * white) == Graphics::Colour::Red);
			}
			SECTION("Test *= operator (float)") {
				float r = 1.0f;
				float g = 1.0f;
				float b = 1.0f;

				float val = 0.5f;

				Graphics::Colour col = Graphics::Colour(r, g, b);

				col *= val;

				REQUIRE(col == Graphics::Colour(r * val, g * val, b * val));
			}
			SECTION("Test *= operator (Colour)") {
				Graphics::Colour red = Graphics::Colour::Red;
				Graphics::Colour white = Graphics::Colour::White;

				red *= white;

				REQUIRE(red == Graphics::Colour::Red);
			}
		}
	}
}