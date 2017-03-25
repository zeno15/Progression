#include <catch.hpp>

#include <System/Transformable2D.hpp>

#define TO_RADIANS(x) (x * 3.14159265f / 180.0f)

namespace System {
	namespace Transformable2DTests {
		TEST_CASE("Transformable2D Test", "[Transformable2D]") {
			SECTION("Test Transformable2D default constructor") {
				auto tf2d = Transformable2D();

				REQUIRE(tf2d.getPosition()  == Vector2f(0.0f, 0.0f));
				REQUIRE(tf2d.getRotation()  == 0.0f);
				REQUIRE(tf2d.getScale()     == Vector2f(1.0f, 1.0f));
				REQUIRE(tf2d.transformPoint(Vector2f(1.0f, 1.0f)) == Vector2f(1.0f, 1.0f));
			}

			SECTION("Test translate method", "[Transformable2D]") {
				auto tf2d = Transformable2D();

				auto translation = Vector2f(5.0f, -76.0f);

				tf2d.translate(translation);

				REQUIRE(translation == tf2d.getPosition());

				tf2d.translate(translation);

				REQUIRE(translation * 2.0f == tf2d.getPosition());

				REQUIRE(tf2d.transformPoint(Vector2f()) == translation * 2.0f);
			}

			SECTION("Test setTranslate method", "[Transformable2D]") {
				auto tf2d = Transformable2D();

				auto translation = Vector2f(5.0f, -76.0f);

				tf2d.setTranslate(translation);

				REQUIRE(translation == tf2d.getPosition());

				tf2d.setTranslate(translation * 2.0f);

				REQUIRE(translation * 2.0f == tf2d.getPosition());

				REQUIRE(tf2d.transformPoint(Vector2f()) == translation * 2.0f);
			}

			SECTION("Test rotate method", "[Transformable2D]") {
				auto tf2d = Transformable2D();

				float rotation = 90.0f;

				tf2d.rotate(rotation);

				REQUIRE(rotation == tf2d.getRotation());

				tf2d.rotate(rotation);

				REQUIRE(rotation * 2.0f == tf2d.getRotation());

				Vector2f point(5.0f, 10.0f);

				REQUIRE(-point.x == Approx((tf2d.transformPoint(point).x)));
				REQUIRE(-point.y == Approx((tf2d.transformPoint(point).y)));
			}
			SECTION("Test setRotation method", "[Transformable2D]") {
				auto tf2d = Transformable2D();

				float rotation = 90.0f;

				tf2d.setRotation(rotation);

				REQUIRE(rotation == tf2d.getRotation());

				tf2d.setRotation(rotation * 2.0f);

				REQUIRE(rotation * 2.0f == tf2d.getRotation());

				Vector2f point(5.0f, 10.0f);

				REQUIRE(-point.x == Approx((tf2d.transformPoint(point).x)));
				REQUIRE(-point.y == Approx((tf2d.transformPoint(point).y)));
			}

			SECTION("Test scale method", "[Transformable2D]") {
				auto tf2d = Transformable2D();

				Vector2f scale(2.0f, 5.0f);

				tf2d.scale(scale);

				REQUIRE(scale == tf2d.getScale());

				tf2d.scale(scale);

				REQUIRE(Vector2f(scale.x * scale.x, scale.y * scale.y) == tf2d.getScale());

				Vector2f point(5.0f, 10.0f);

				REQUIRE(Vector2f(point.x * scale.x * scale.x, point.y * scale.y * scale.y) == tf2d.transformPoint(point));
			}

			SECTION("Test setScale method", "[Transformable2D]") {
				auto tf2d = Transformable2D();

				Vector2f scale(2.0f, 5.0f);

				tf2d.setScale(scale);

				REQUIRE(scale == tf2d.getScale());

				tf2d.setScale(Vector2f(scale.x * scale.x, scale.y * scale.y));

				REQUIRE(Vector2f(scale.x * scale.x, scale.y * scale.y) == tf2d.getScale());

				Vector2f point(5.0f, 10.0f);

				REQUIRE(Vector2f(point.x * scale.x * scale.x, point.y * scale.y * scale.y) == tf2d.transformPoint(point));
			}

			SECTION("Test resetTransformable method", "[Transformable2D]") {
				auto tf2d = Transformable2D();

				auto translation = Vector2f(5.0f, -76.0f);

				tf2d.translate(translation);

				REQUIRE(translation == tf2d.getPosition());

				tf2d.resetTransformable();

				REQUIRE(Vector2f() == tf2d.getPosition());
			}

			SECTION("Test translate, rotate and scale simultaneously", "[Transformable2D]") {
				auto tf2d = Transformable2D();

				Vector2f translation(5.0f, -76.0f);
				Vector2f scale(2.0f, 5.0f);
				float rotation = 90.0f;

				tf2d.translate(translation);
				tf2d.scale(scale);
				tf2d.rotate(rotation);

				Vector2f point(1.0f, 1.0f);

				Vector2f result = tf2d.transformPoint(point);

				REQUIRE(translation == tf2d.getPosition());
				REQUIRE(scale       == tf2d.getScale());
				REQUIRE(rotation    == tf2d.getRotation());

				REQUIRE(result == Vector2f(
					point.x * (std::cosf(TO_RADIANS(rotation)) - std::sinf(TO_RADIANS(rotation))) * scale.x + translation.x,
					point.y * (std::cosf(TO_RADIANS(rotation)) + std::sinf(TO_RADIANS(rotation))) * scale.y + translation.y));
			}
		}
	}
}