#include <Tower/TowerStart.hpp>

#include <Tower/TowerDefinitions.hpp>
#include <Tower/TowerResources.hpp>

#include <Tower/Managers/CreepManager.hpp>
#include <Tower/Managers/EconomyManager.hpp>
#include <Tower/Managers/LevelManager.hpp>
#include <Tower/Managers/LevelInteractionManager.hpp>
#include <Tower/Managers/NotificationManager.hpp>
#include <Tower/Managers/ProjectileManager.hpp>
#include <Tower/Managers/TowerManager.hpp>
#include <Tower/Managers/UserInteractionManager.hpp>

#include <Tower/Scenes/TowerGameScene.hpp>

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

namespace Tower {

	void Tower::initialiseManagers(void) {
		Infrastructure::InstanceCollection::registerInstance<Infrastructure::Application>();
		Infrastructure::InstanceCollection::registerInstance<Infrastructure::Camera>();
		Infrastructure::InstanceCollection::registerInstance<Infrastructure::FontManager>();
		Infrastructure::InstanceCollection::registerInstance<Infrastructure::SceneManager>();
		Infrastructure::InstanceCollection::registerInstance<Infrastructure::ShaderManager>();
		Infrastructure::InstanceCollection::registerInstance<Infrastructure::TextureManager>();

		Infrastructure::InstanceCollection::registerInstance<CreepManager>();
		Infrastructure::InstanceCollection::registerInstance<EconomyManager>();
		Infrastructure::InstanceCollection::registerInstance<LevelManager>();
		Infrastructure::InstanceCollection::registerInstance<LevelInteractionManager>();
		Infrastructure::InstanceCollection::registerInstance<NotificationManager>();
		Infrastructure::InstanceCollection::registerInstance<ProjectileManager>();
		Infrastructure::InstanceCollection::registerInstance<TowerManager>();
		Infrastructure::InstanceCollection::registerInstance<UserInteractionManager>();
	}
	void Tower::loadResources(void) {
		Infrastructure::InstanceCollection::getInstance<Infrastructure::FontManager>().addFont(TowerResources::DefaultFontFilename, TowerResources::DefaultFontName);

		Infrastructure::InstanceCollection::getInstance<Infrastructure::ShaderManager>().addShader(TowerResources::SolidNoTextureShaderName, TowerResources::SolidNoTextureShaderVertexPath, TowerResources::SolidNoTextureShaderFragmentPath);
		Infrastructure::InstanceCollection::getInstance<Infrastructure::ShaderManager>().getShader(TowerResources::SolidNoTextureShaderName).getLocationOfUniforms({
			TowerResources::SolidNoTextureShaderUniformMVP,
			TowerResources::SolidNoTextureShaderUniformColour
		});

		Infrastructure::InstanceCollection::getInstance<Infrastructure::ShaderManager>().addShader(TowerResources::TextShaderName, TowerResources::TextShaderVertexPath, TowerResources::TextShaderFragmentPath);
		Infrastructure::InstanceCollection::getInstance<Infrastructure::ShaderManager>().getShader(TowerResources::TextShaderName).getLocationOfUniforms({
			TowerResources::TextShaderUniformView,
			TowerResources::TextShaderUniformTexSize,
			TowerResources::TextShaderUniformColour
		});

		Infrastructure::InstanceCollection::getInstance<Infrastructure::ShaderManager>().addShader(TowerResources::VertexArrayNoTextureShaderName, TowerResources::VertexArrayNoTextureShaderVertexPath, TowerResources::VertexArrayNoTextureShaderFragmentPath);
		Infrastructure::InstanceCollection::getInstance<Infrastructure::ShaderManager>().getShader(TowerResources::VertexArrayNoTextureShaderName).getLocationOfUniforms({
			TowerResources::VertexArrayNoTextureShaderUniformMVP,
		});

		Infrastructure::InstanceCollection::getInstance<NotificationManager>().onCreepKilled.registerCallback([](Creep *_creep) {
			Infrastructure::InstanceCollection::getInstance<LevelManager>().onCreepKilled(_creep);
			Infrastructure::InstanceCollection::getInstance<TowerManager>().onCreepKilled(_creep);
			Infrastructure::InstanceCollection::getInstance<ProjectileManager>().onCreepKilled(_creep);
		});
		Infrastructure::InstanceCollection::getInstance<NotificationManager>().onCreepReachesEnd.registerCallback([](Creep *_creep) {
			Infrastructure::InstanceCollection::getInstance<LevelManager>().onCreepReachedEnd(_creep);
			Infrastructure::InstanceCollection::getInstance<TowerManager>().onCreepReachedEnd(_creep);
			Infrastructure::InstanceCollection::getInstance<ProjectileManager>().onCreepReachedEnd(_creep);
		});
	}
	void Tower::start(void) {
		Infrastructure::InstanceCollection::getInstance<Infrastructure::Application>().initialise(System::Vector2u(1280, 720), "Tower");
		Infrastructure::InstanceCollection::getInstance<Infrastructure::Camera>().setPosition(System::Vector2f(620.0f, 320.0f));

		glClearColor(0.0f / 255.0f, 65.0f / 255.0f, 125.0f / 255.0f, 1.0f);

		srand(static_cast<unsigned int>(time(nullptr)));

		loadResources();

		auto scene = new TowerGameScene();

		Infrastructure::InstanceCollection::getInstance<Infrastructure::SceneManager>().addScene(scene);
		Infrastructure::InstanceCollection::getInstance<Infrastructure::SceneManager>().setActiveScene(scene);

		Infrastructure::InstanceCollection::getInstance<Infrastructure::Application>().start();
	}

}