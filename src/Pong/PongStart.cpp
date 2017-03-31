#include <Pong/PongStart.hpp>

#include <Pong/Scenes/PongGameScene.hpp>

#include <Infrastructure/Application.hpp>
#include <Infrastructure/FontManager.hpp>
#include <Infrastructure/InstanceCollection.hpp>
#include <Infrastructure/SceneManager.hpp>
#include <Infrastructure/ShaderManager.hpp>
#include <Infrastructure/TextureManager.hpp>

namespace Pong {
	void initialiseManagers(void) {
		Infrastructure::InstanceCollection::registerInstance<Infrastructure::Application>();
		Infrastructure::InstanceCollection::registerInstance<Infrastructure::FontManager>();
		Infrastructure::InstanceCollection::registerInstance<Infrastructure::SceneManager>();
		Infrastructure::InstanceCollection::registerInstance<Infrastructure::ShaderManager>();
		Infrastructure::InstanceCollection::registerInstance<Infrastructure::TextureManager>();
	}

	void start(void) {

		Infrastructure::InstanceCollection::getInstance<Infrastructure::Application>().initialise(System::Vector2u(1280, 720), "Pong");
		glClearColor(0.0f / 255.0f, 225.0f / 255.0f, 65.0f / 255.0f, 1.0f);
		
		auto scene = new PongGameScene();

		Infrastructure::InstanceCollection::getInstance<Infrastructure::SceneManager>().addScene(scene);
		Infrastructure::InstanceCollection::getInstance<Infrastructure::SceneManager>().setActiveScene(scene);

		Infrastructure::InstanceCollection::getInstance<Infrastructure::Application>().start();
	}
}