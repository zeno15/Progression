#include <catch.hpp>

#include <Infrastructure/SceneManager.hpp>
#include <Infrastructure/InstanceCollection.hpp>


namespace Infrastructure {
	namespace SceneManagerTests {
		class SceneManagerTestScene : public Scene {
		public:
			SceneManagerTestScene(const std::string& _name) : Scene(_name), m_UValue(0), m_FValue(0.0f) {}
			void update(float _delta) override {
				m_UValue += 1;
				m_FValue += _delta;
			}
			bool handleEvent(const System::Event& _event) { return false; };
			void render(const Window::Window& _window, Graphics::RenderData _states) const override {};

			unsigned int m_UValue;
			float m_FValue;
		};

		TEST_CASE("Scene is only activated when explicitly ordered to", "[SceneManager]") {
			InstanceCollection::clear();
			InstanceCollection::registerInstance<SceneManager>();
			auto& sceneManager = InstanceCollection::getInstance<SceneManager>();
			const std::string name = "SceneManagerTestScene";


			auto testScene = new SceneManagerTestScene(name);

			sceneManager.addScene(testScene);

			sceneManager.setActiveScene(testScene);

			REQUIRE(sceneManager.getActiveScene().getName() == name);
			REQUIRE(sceneManager.getScene(name).getName() == name);
			REQUIRE_THROWS(sceneManager.getScene("Not present scene"));
		}

		TEST_CASE("Updating scene manager updates scene width correct delta values", "[SceneManager]") {
			InstanceCollection::clear();
			InstanceCollection::registerInstance<SceneManager>();
			auto& sceneManager = InstanceCollection::getInstance<SceneManager>();
			const std::string name = "SceneManagerTestScene";
			auto testScene = SceneManagerTestScene(name);

			sceneManager.addScene(&testScene);
			sceneManager.setActiveScene(&testScene);

			float delta = 1.0f;
			
			for (unsigned int i = 1; i < 10; i += 1) {
				sceneManager.update(delta);
				REQUIRE(sceneManager.getScene<SceneManagerTestScene>(name).m_UValue == i);
				REQUIRE(sceneManager.getScene<SceneManagerTestScene>(name).m_FValue == delta * i);
			}
		}
	}
}