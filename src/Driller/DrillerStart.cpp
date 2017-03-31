#include <Driller/DrillerStart.hpp>

#include <Driller/DrillerResources.hpp>

#include <Driller/Managers/Camera.hpp>
#include <Driller/Managers/JobManager.hpp>
#include <Driller/Managers/NotificationService.hpp>
#include <Driller/Managers/RoomManager.hpp>
#include <Driller/Managers/TileManager.hpp>
#include <Driller/Managers/UserInteractionManager.hpp>
#include <Driller/Managers/WorkerManager.hpp>

#include <Driller/Scenes/DrillerGameScene.hpp>

#include <Infrastructure/Application.hpp>
#include <Infrastructure/InstanceCollection.hpp>
#include <Infrastructure/FontManager.hpp>
#include <Infrastructure/SceneManager.hpp>
#include <Infrastructure/ShaderManager.hpp>
#include <Infrastructure/TextureManager.hpp>

#include <iostream>

namespace Driller {

	void initialiseManagers(void) {
		Infrastructure::InstanceCollection::registerInstance<Infrastructure::Application>();
		Infrastructure::InstanceCollection::registerInstance<Infrastructure::FontManager>();
		Infrastructure::InstanceCollection::registerInstance<Infrastructure::SceneManager>();
		Infrastructure::InstanceCollection::registerInstance<Infrastructure::ShaderManager>();
		Infrastructure::InstanceCollection::registerInstance<Infrastructure::TextureManager>();

		Infrastructure::InstanceCollection::registerInstance<Camera>();
		Infrastructure::InstanceCollection::registerInstance<JobManager>();
		Infrastructure::InstanceCollection::registerInstance<NotificationService>();
		Infrastructure::InstanceCollection::registerInstance<RoomManager>();
		Infrastructure::InstanceCollection::registerInstance<TileManager>();
		Infrastructure::InstanceCollection::registerInstance<UserInteractionManager>();
		Infrastructure::InstanceCollection::registerInstance<WorkerManager>();
	}

	void bindCallbacks(void) {
		Infrastructure::InstanceCollection::getInstance<NotificationService>().OnTileActivated.registerCallback(
			std::bind(
				&TileManager::onTileActivated, 
				Infrastructure::InstanceCollection::getInstance<TileManager>(),
				std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	}
	
	void loadResources(void) {
		Infrastructure::InstanceCollection::getInstance<Infrastructure::FontManager>().addFont(DrillerResources::DefaultFontFilename, DrillerResources::DefaultFontName);
		Infrastructure::InstanceCollection::getInstance<Infrastructure::TextureManager>().addTexture(DrillerResources::SpriteSheetFilename, DrillerResources::SpriteSheetName);

		Infrastructure::InstanceCollection::getInstance<Infrastructure::ShaderManager>().addShader(DrillerResources::TestShaderName, DrillerResources::TestShaderVertexFilename, DrillerResources::TestShaderFragmentFilename);
		Infrastructure::InstanceCollection::getInstance<Infrastructure::ShaderManager>().getShader(DrillerResources::TestShaderName).getLocationOfUniforms({
			DrillerResources::TestShaderMVPUniformName,
			DrillerResources::TestShaderColourUniformName
		});

		Infrastructure::InstanceCollection::getInstance<Infrastructure::ShaderManager>().addShader(DrillerResources::BuildingGhostShaderName, DrillerResources::BuildingGhostShaderVertexFilename, DrillerResources::BuildingGhostShaderFragmentFilename);
		Infrastructure::InstanceCollection::getInstance<Infrastructure::ShaderManager>().getShader(DrillerResources::BuildingGhostShaderName).getLocationOfUniforms({
			DrillerResources::BuildingGhostShaderMVPUniformName,
			DrillerResources::BuildingGhostShaderColourUniformName
		});

		Infrastructure::InstanceCollection::getInstance<Infrastructure::ShaderManager>().addShader(DrillerResources::StaticTexturedShaderName, DrillerResources::StaticTexturedShaderVertexFilename, DrillerResources::StaticTexturedShaderFragmentFilename);
		Infrastructure::InstanceCollection::getInstance<Infrastructure::ShaderManager>().getShader(DrillerResources::StaticTexturedShaderName).getLocationOfUniforms({
			DrillerResources::StaticTexturedShaderMVPUniformName
		});
	}

	void start(void) {
		Infrastructure::InstanceCollection::getInstance<Infrastructure::Application>().initialise(System::Vector2u(1440, 900), "Driller");
		glClearColor(183.0f / 255.0f, 68.0f / 255.0f, 14.0f / 255.0f, 1.0f);

		Driller::bindCallbacks();

		Driller::loadResources();

		auto scene = new DrillerGameScene();

		Infrastructure::InstanceCollection::getInstance<WorkerManager>().addWorker(new WorkerElement());

		Infrastructure::InstanceCollection::getInstance<Infrastructure::SceneManager>().addScene(scene);
		Infrastructure::InstanceCollection::getInstance<Infrastructure::SceneManager>().setActiveScene(scene);

		Infrastructure::InstanceCollection::getInstance<Infrastructure::Application>().start();
	}
}