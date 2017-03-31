#include <Pong/PongStart.hpp>

#include <Pong/PongResources.hpp>

#include <Pong/Scenes/PongGameScene.hpp>

#include <Pong/Managers/GameObjectManager.hpp>
#include <Pong/Managers/NotificationManager.hpp>

#include <Infrastructure/Application.hpp>
#include <Infrastructure/Camera.hpp>
#include <Infrastructure/FontManager.hpp>
#include <Infrastructure/InstanceCollection.hpp>
#include <Infrastructure/SceneManager.hpp>
#include <Infrastructure/ShaderManager.hpp>
#include <Infrastructure/TextureManager.hpp>

#include <ctime>
#include <cstdlib>
#include <functional>

namespace Pong {
	void initialiseManagers(void) {
		Infrastructure::InstanceCollection::registerInstance<Infrastructure::Application>();
		Infrastructure::InstanceCollection::registerInstance<Infrastructure::Camera>();
		Infrastructure::InstanceCollection::registerInstance<Infrastructure::FontManager>();
		Infrastructure::InstanceCollection::registerInstance<Infrastructure::SceneManager>();
		Infrastructure::InstanceCollection::registerInstance<Infrastructure::ShaderManager>();
		Infrastructure::InstanceCollection::registerInstance<Infrastructure::TextureManager>();

		Infrastructure::InstanceCollection::registerInstance<GameObjectManager>();
		Infrastructure::InstanceCollection::registerInstance<NotificationManager>();
	}

	void loadResources(void) {
		Infrastructure::InstanceCollection::getInstance<Infrastructure::FontManager>().addFont(PongResources::DefaultFontFilename, PongResources::DefaultFontName);

		Infrastructure::InstanceCollection::getInstance<Infrastructure::ShaderManager>().addShader(PongResources::SolidNoTextureShaderName, PongResources::SolidNoTextureShaderVertexPath, PongResources::SolidNoTextureShaderFragmentPath);
		Infrastructure::InstanceCollection::getInstance<Infrastructure::ShaderManager>().getShader(PongResources::SolidNoTextureShaderName).getLocationOfUniforms({
			PongResources::SolidNoTextureShaderUniformMVP,
			PongResources::SolidNoTextureShaderUniformColour
		});

		Infrastructure::InstanceCollection::getInstance<Infrastructure::ShaderManager>().addShader(PongResources::TextShaderName, PongResources::TextShaderVertexPath, PongResources::TextShaderFragmentPath);
		Infrastructure::InstanceCollection::getInstance<Infrastructure::ShaderManager>().getShader(PongResources::TextShaderName).getLocationOfUniforms({
			PongResources::TextShaderUniformView,
			PongResources::TextShaderUniformTexSize,
			PongResources::TextShaderUniformColour
		});
	}

	void registerCallbacks(void) {
		Infrastructure::InstanceCollection::getInstance<NotificationManager>().onBallLost.registerCallback(
			std::bind(
				&PongGameScene::ballLost, 
				Infrastructure::InstanceCollection::getInstance<Infrastructure::SceneManager>().getScene<PongGameScene>("PongGameScene"), 
				std::placeholders::_1,
				std::placeholders::_2));
	}

	void start(void) {
		Infrastructure::InstanceCollection::getInstance<Infrastructure::Application>().initialise(System::Vector2u(1280, 720), "Pong");
		glClearColor(0.0f / 255.0f, 225.0f / 255.0f, 65.0f / 255.0f, 1.0f);

		srand(static_cast<unsigned int>(time(nullptr)));

		loadResources();
		
		auto scene = new PongGameScene();

		Infrastructure::InstanceCollection::getInstance<Infrastructure::SceneManager>().addScene(scene);
		Infrastructure::InstanceCollection::getInstance<Infrastructure::SceneManager>().setActiveScene(scene);

		registerCallbacks();

		Infrastructure::InstanceCollection::getInstance<Infrastructure::Application>().start();
	}
}