#include <catch.hpp>

#include <Infrastructure/Scene.hpp>

namespace Infrastructure {
	namespace SceneTests {
		class TestScene : public Scene {
		public:
			TestScene(const std::string& _name) : Scene(_name) {}
			void update(float _delta) override {}
			bool handleEvent(const sf::Event& _event) { return false; };
			void draw(sf::RenderTarget& _target, sf::RenderStates _states) const {};
		};

		TEST_CASE("Scene sets its name correctly", "[Scene]") {
			std::string name = "TestSceneName";

			auto testScene = TestScene(name);

			REQUIRE(testScene.getName() == name);
		}
	}
}