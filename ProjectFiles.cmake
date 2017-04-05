# Copyright (c) 2017 Mark Davison (markdavison0@gmail.com)
# Distributed under the MIT License.
# See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT




# Header files
SET(ECS_INCLUDE_FILES ${ECS_INCLUDE_FILES}
	${CMAKE_SOURCE_DIR}/include/ECS/Component.hpp
	${CMAKE_SOURCE_DIR}/include/ECS/Entity.hpp
	${CMAKE_SOURCE_DIR}/include/ECS/EntityManager.hpp
	${CMAKE_SOURCE_DIR}/include/ECS/System.hpp
)

SET(GRAPHICS_INCLUDE_FILES ${GRAPHICS_INCLUDE_FILES}
	${CMAKE_SOURCE_DIR}/include/Graphics/AnimatedSprite.hpp
	${CMAKE_SOURCE_DIR}/include/Graphics/Colour.hpp
	${CMAKE_SOURCE_DIR}/include/Graphics/Font.hpp
	${CMAKE_SOURCE_DIR}/include/Graphics/Glyph.hpp
	${CMAKE_SOURCE_DIR}/include/Graphics/Image.hpp
	${CMAKE_SOURCE_DIR}/include/Graphics/ImageLoader.hpp
	${CMAKE_SOURCE_DIR}/include/Graphics/Renderable.hpp
	${CMAKE_SOURCE_DIR}/include/Graphics/RenderData.hpp
	${CMAKE_SOURCE_DIR}/include/Graphics/Shader.hpp
	${CMAKE_SOURCE_DIR}/include/Graphics/Text.hpp
	${CMAKE_SOURCE_DIR}/include/Graphics/Texture.hpp
	${CMAKE_SOURCE_DIR}/include/Graphics/Vertex.hpp
	${CMAKE_SOURCE_DIR}/include/Graphics/VertexArray.hpp
	
)

SET(INFRASTRUCTURE_INCLUDE_FILES ${INFRASTRUCTURE_INCLUDE_FILES}
	${CMAKE_SOURCE_DIR}/include/Infrastructure/Application.hpp
	${CMAKE_SOURCE_DIR}/include/Infrastructure/Camera.hpp
	${CMAKE_SOURCE_DIR}/include/Infrastructure/FontManager.hpp
	${CMAKE_SOURCE_DIR}/include/Infrastructure/InstanceCollection.hpp
	${CMAKE_SOURCE_DIR}/include/Infrastructure/Manager.hpp
	${CMAKE_SOURCE_DIR}/include/Infrastructure/Scene.hpp
	${CMAKE_SOURCE_DIR}/include/Infrastructure/SceneManager.hpp
	${CMAKE_SOURCE_DIR}/include/Infrastructure/ShaderManager.hpp
	${CMAKE_SOURCE_DIR}/include/Infrastructure/Signal.hpp
	${CMAKE_SOURCE_DIR}/include/Infrastructure/TextureManager.hpp


	${CMAKE_SOURCE_DIR}/include/Infrastructure.hpp
)

SET(SYSTEM_INCLUDE_FILES ${SYSTEM_INCLUDE_FILES}
	${CMAKE_SOURCE_DIR}/include/System/Clock.hpp
	${CMAKE_SOURCE_DIR}/include/System/Event.hpp
	${CMAKE_SOURCE_DIR}/include/System/InputImplementation.hpp
	${CMAKE_SOURCE_DIR}/include/System/InputImplementationWin32.hpp
	${CMAKE_SOURCE_DIR}/include/System/Keyboard.hpp
	${CMAKE_SOURCE_DIR}/include/System/Mat4x4.hpp
	${CMAKE_SOURCE_DIR}/include/System/Mouse.hpp
	${CMAKE_SOURCE_DIR}/include/System/Rect.hpp
	${CMAKE_SOURCE_DIR}/include/System/Time.hpp
	${CMAKE_SOURCE_DIR}/include/System/Transformable2D.hpp
	${CMAKE_SOURCE_DIR}/include/System/Vector2.hpp
	${CMAKE_SOURCE_DIR}/include/System/Vector3.hpp
	${CMAKE_SOURCE_DIR}/include/System/Vector4.hpp
	${CMAKE_SOURCE_DIR}/include/System/VectorMath.hpp
)

SET(UTILITY_INCLUDE_FILES ${UTILITY_INCLUDE_FILES}
	${CMAKE_SOURCE_DIR}/include/Utility/StringHelper.hpp
	${CMAKE_SOURCE_DIR}/include/Utility/XML.hpp
)

SET(WINDOW_INCLUDE_FILES ${WINDOW_INCLUDE_FILES}
	${CMAKE_SOURCE_DIR}/include/Window/ContextImplementation.hpp
	${CMAKE_SOURCE_DIR}/include/Window/ContextWin32.hpp
	${CMAKE_SOURCE_DIR}/include/Window/OpenGL.hpp
	${CMAKE_SOURCE_DIR}/include/Window/OpenGLDefinitions.hpp
	${CMAKE_SOURCE_DIR}/include/Window/OpenGLDefinitionsWindows.hpp
	${CMAKE_SOURCE_DIR}/include/Window/VideoMode.hpp
	${CMAKE_SOURCE_DIR}/include/Window/Window.hpp
	${CMAKE_SOURCE_DIR}/include/Window/WindowImplementation.hpp
	${CMAKE_SOURCE_DIR}/include/Window/WindowImplementationWin32.hpp
	${CMAKE_SOURCE_DIR}/include/Window/WindowStyle.hpp
)

SET(DRILLER_INCLUDE_FILES ${DRILLER_INCLUDE_FILES}
	${CMAKE_SOURCE_DIR}/include/Driller/Components/RenderComponent.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/Components/TransformationComponent.hpp

	${CMAKE_SOURCE_DIR}/include/Driller/DrillerDefinitions.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/DrillerResources.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/DrillerStart.hpp
	
	${CMAKE_SOURCE_DIR}/include/Driller/Elements/BaseElement.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/Elements/ElementHelpers.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/Elements/ElevatorShaftElement.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/Elements/JobElement.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/Elements/RoomElement.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/Elements/UndergroundTileElement.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/Elements/WorkerElement.hpp
	
	${CMAKE_SOURCE_DIR}/include/Driller/Managers/JobManager.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/Managers/NotificationService.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/Managers/RoomManager.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/Managers/TileManager.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/Managers/UserInteractionManager.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/Managers/WorkerManager.hpp

	${CMAKE_SOURCE_DIR}/include/Driller/Models/JobContextInfo.hpp
	
	${CMAKE_SOURCE_DIR}/include/Driller/Scenes/DrillerGameScene.hpp

	${CMAKE_SOURCE_DIR}/include/Driller/Systems/RenderSystem.hpp
)

SET(PONG_INCLUDE_FILES ${PONG_INCLUDE_FILES}
	${CMAKE_SOURCE_DIR}/include/Pong/PongDefinitions.hpp
	${CMAKE_SOURCE_DIR}/include/Pong/PongResources.hpp
	${CMAKE_SOURCE_DIR}/include/Pong/PongStart.hpp
	
	${CMAKE_SOURCE_DIR}/include/Pong/GameObjects/Ball.hpp
	${CMAKE_SOURCE_DIR}/include/Pong/GameObjects/Board.hpp
	${CMAKE_SOURCE_DIR}/include/Pong/GameObjects/GameObject.hpp
	${CMAKE_SOURCE_DIR}/include/Pong/GameObjects/Paddle.hpp
	
	${CMAKE_SOURCE_DIR}/include/Pong/Managers/GameObjectManager.hpp
	${CMAKE_SOURCE_DIR}/include/Pong/Managers/NotificationManager.hpp

	${CMAKE_SOURCE_DIR}/include/Pong/Scenes/PongGameScene.hpp
)

SET(INCLUDE_FILES ${INCLUDE_FILES}
	${ECS_INCLUDE_FILES}
	${GRAPHICS_INCLUDE_FILES}
	${INFRASTRUCTURE_INCLUDE_FILES}
	${SYSTEM_INCLUDE_FILES}
	${UTILITY_INCLUDE_FILES}
	${WINDOW_INCLUDE_FILES}

	${DRILLER_INCLUDE_FILES}
	${PONG_INCLUDE_FILES}
)

SET(THIRD_PARTY_STB_INCLUDE_FILES ${THIRD_PARTY_STB_INCLUDE_FILES}
	${CMAKE_SOURCE_DIR}/thirdparty/stb/stb_image.h
	${CMAKE_SOURCE_DIR}/thirdparty/stb/stb_image_write.h
)

SET(THIRD_PARTY_INCLUDE_FILES ${THIRD_PARTY_INCLUDE_FILES}
	${THIRD_PARTY_STB_INCLUDE_FILES}
)


# Source files
SET(ECS_SOURCE_FILES ${ECS_SOURCE_FILES}
	${CMAKE_SOURCE_DIR}/src/ECS/Component.cpp
	${CMAKE_SOURCE_DIR}/src/ECS/EntityManager.cpp
)

SET (GRAPHICS_SOURCE_FILES ${GRAPHICS_SOURCE_FILES}
	${CMAKE_SOURCE_DIR}/src/Graphics/AnimatedSprite.cpp
	${CMAKE_SOURCE_DIR}/src/Graphics/Colour.cpp
	${CMAKE_SOURCE_DIR}/src/Graphics/Font.cpp
	${CMAKE_SOURCE_DIR}/src/Graphics/Glyph.cpp
	${CMAKE_SOURCE_DIR}/src/Graphics/Image.cpp
	${CMAKE_SOURCE_DIR}/src/Graphics/ImageLoader.cpp
	${CMAKE_SOURCE_DIR}/src/Graphics/RenderData.cpp
	${CMAKE_SOURCE_DIR}/src/Graphics/Shader.cpp
	${CMAKE_SOURCE_DIR}/src/Graphics/Text.cpp
	${CMAKE_SOURCE_DIR}/src/Graphics/Texture.cpp
	${CMAKE_SOURCE_DIR}/src/Graphics/Vertex.cpp
	${CMAKE_SOURCE_DIR}/src/Graphics/VertexArray.cpp
)

SET (INFRASTRUCTURE_SOURCE_FILES ${INFRASTRUCTURE_SOURCE_FILES}
	${CMAKE_SOURCE_DIR}/src/Infrastructure/Application.cpp
	${CMAKE_SOURCE_DIR}/src/Infrastructure/Camera.cpp
	${CMAKE_SOURCE_DIR}/src/Infrastructure/FontManager.cpp
	${CMAKE_SOURCE_DIR}/src/Infrastructure/InstanceCollection.cpp
	${CMAKE_SOURCE_DIR}/src/Infrastructure/Scene.cpp
	${CMAKE_SOURCE_DIR}/src/Infrastructure/SceneManager.cpp
	${CMAKE_SOURCE_DIR}/src/Infrastructure/ShaderManager.cpp
	${CMAKE_SOURCE_DIR}/src/Infrastructure/TextureManager.cpp
)

SET(UTILITY_SOURCE_FILES ${UTILITY_SOURCE_FILES}
	${CMAKE_SOURCE_DIR}/src/Utility/StringHelper.cpp
	${CMAKE_SOURCE_DIR}/src/Utility/XML.cpp
)

SET(SYSTEM_SOURCE_FILES ${SYSTEM_SOURCE_FILES}
	${CMAKE_SOURCE_DIR}/src/System/Clock.cpp
	${CMAKE_SOURCE_DIR}/src/System/InputImplementationWin32.cpp
	${CMAKE_SOURCE_DIR}/src/System/Keyboard.cpp
	${CMAKE_SOURCE_DIR}/src/System/Mat4x4.cpp
	${CMAKE_SOURCE_DIR}/src/System/Mouse.cpp
	${CMAKE_SOURCE_DIR}/src/System/Time.cpp
	${CMAKE_SOURCE_DIR}/src/System/Transformable2D.cpp
)

SET(WINDOW_SOURCE_FILES ${WINDOW_SOURCE_FILES}
	${CMAKE_SOURCE_DIR}/src/Window/ContextWin32.cpp
	${CMAKE_SOURCE_DIR}/src/Window/OpenGL.cpp
	${CMAKE_SOURCE_DIR}/src/Window/Window.cpp
	${CMAKE_SOURCE_DIR}/src/Window/WindowImplementationWin32.cpp
)

SET(DRILLER_SOURCE_FILES ${DRILLER_SOURCE_FILES}
	${CMAKE_SOURCE_DIR}/src/Driller/Components/RenderComponent.cpp
	${CMAKE_SOURCE_DIR}/src/Driller/Components/TransformationComponent.cpp

	${CMAKE_SOURCE_DIR}/src/Driller/DrillerDefinitions.cpp
	${CMAKE_SOURCE_DIR}/src/Driller/DrillerResources.cpp
	${CMAKE_SOURCE_DIR}/src/Driller/DrillerStart.cpp
	
	${CMAKE_SOURCE_DIR}/src/Driller/Elements/BaseElement.cpp
	${CMAKE_SOURCE_DIR}/src/Driller/Elements/ElementHelpers.cpp
	${CMAKE_SOURCE_DIR}/src/Driller/Elements/ElevatorShaftElement.cpp
	${CMAKE_SOURCE_DIR}/src/Driller/Elements/JobElement.cpp
	${CMAKE_SOURCE_DIR}/src/Driller/Elements/RoomElement.cpp
	${CMAKE_SOURCE_DIR}/src/Driller/Elements/UndergroundTileElement.cpp
	${CMAKE_SOURCE_DIR}/src/Driller/Elements/WorkerElement.cpp
	
	${CMAKE_SOURCE_DIR}/src/Driller/Managers/JobManager.cpp
	${CMAKE_SOURCE_DIR}/src/Driller/Managers/NotificationService.cpp
	${CMAKE_SOURCE_DIR}/src/Driller/Managers/RoomManager.cpp
	${CMAKE_SOURCE_DIR}/src/Driller/Managers/TileManager.cpp
	${CMAKE_SOURCE_DIR}/src/Driller/Managers/UserInteractionManager.cpp
	${CMAKE_SOURCE_DIR}/src/Driller/Managers/WorkerManager.cpp
	
	${CMAKE_SOURCE_DIR}/src/Driller/Scenes/DrillerGameScene.cpp

	${CMAKE_SOURCE_DIR}/src/Driller/Systems/RenderSystem.cpp
)

SET(PONG_SOURCE_FILES ${PONG_SOURCE_FILES}
	${CMAKE_SOURCE_DIR}/src/Pong/PongDefinitions.cpp
	${CMAKE_SOURCE_DIR}/src/Pong/PongResources.cpp
	${CMAKE_SOURCE_DIR}/src/Pong/PongStart.cpp
	
	${CMAKE_SOURCE_DIR}/src/Pong/GameObjects/Ball.cpp
	${CMAKE_SOURCE_DIR}/src/Pong/GameObjects/Board.cpp
	${CMAKE_SOURCE_DIR}/src/Pong/GameObjects/GameObject.cpp
	${CMAKE_SOURCE_DIR}/src/Pong/GameObjects/Paddle.cpp
	
	${CMAKE_SOURCE_DIR}/src/Pong/Managers/GameObjectManager.cpp
	${CMAKE_SOURCE_DIR}/src/Pong/Managers/NotificationManager.cpp

	${CMAKE_SOURCE_DIR}/src/Pong/Scenes/PongGameScene.cpp
)

SET(SOURCE_FILES ${SOURCE_FILES}
	${ECS_SOURCE_FILES}
	${GRAPHICS_SOURCE_FILES}
	${INFRASTRUCTURE_SOURCE_FILES}
	${SYSTEM_SOURCE_FILES}
	${UTILITY_SOURCE_FILES}
	${WINDOW_SOURCE_FILES}

	${DRILLER_SOURCE_FILES}
	${PONG_SOURCE_FILES}
)


# Test files
SET(ECS_TEST_SOURCE_FILES ${ECS_TEST_SOURCE_FILES}
	${CMAKE_SOURCE_DIR}/test/ECS/EntityTests.cpp
	${CMAKE_SOURCE_DIR}/test/ECS/EntityManagerTests.cpp
	${CMAKE_SOURCE_DIR}/test/ECS/ComponentTests.cpp
	${CMAKE_SOURCE_DIR}/test/ECS/SystemTests.cpp
)

SET(ECS_TEST_SOURCE_FILES ${ECS_TEST_SOURCE_FILES}	
	${CMAKE_SOURCE_DIR}/test/Graphics/ColourTests.cpp
)

SET (INFRASTRUCTURE_TEST_SOURCE_FILES ${INFRASTRUCTURE_TEST_SOURCE_FILES}
	${CMAKE_SOURCE_DIR}/test/Infrastructure/ApplicationTests.cpp
	${CMAKE_SOURCE_DIR}/test/Infrastructure/InstanceCollectionTests.cpp
	${CMAKE_SOURCE_DIR}/test/Infrastructure/SceneTests.cpp
	${CMAKE_SOURCE_DIR}/test/Infrastructure/SceneManagerTests.cpp
	${CMAKE_SOURCE_DIR}/test/Infrastructure/SignalTests.cpp
)

SET(SYSTEM_TEST_SOURCE_FILES ${SYSTEM_TEST_SOURCE_FILES}
	${CMAKE_SOURCE_DIR}/test/System/Mat4x4Tests.cpp
	${CMAKE_SOURCE_DIR}/test/System/RectTests.cpp
	${CMAKE_SOURCE_DIR}/test/System/TimeTests.cpp
	${CMAKE_SOURCE_DIR}/test/System/Transformable2DTests.cpp
	${CMAKE_SOURCE_DIR}/test/System/Vector2Tests.cpp
	${CMAKE_SOURCE_DIR}/test/System/Vector3Tests.cpp
	${CMAKE_SOURCE_DIR}/test/System/Vector4Tests.cpp
)

SET (UTILITY_TEST_SOURCE_FILES ${UTILITY_TEST_SOURCE_FILES}
	${CMAKE_SOURCE_DIR}/test/Utility/StringHelperTests.cpp
	${CMAKE_SOURCE_DIR}/test/Utility/XMLTests.cpp
)

SET(TEST_SOURCE_FILES ${TEST_SOURCE_FILES}
	${ECS_TEST_SOURCE_FILES}
	${INFRASTRUCTURE_TEST_SOURCE_FILES}
	${SYSTEM_TEST_SOURCE_FILES}
	${UTILITY_TEST_SOURCE_FILES}
)

SET(TEST_INCLUDE_FILES ${TEST_INCLUDE_FILES}
	${CMAKE_SOURCE_DIR}/test/include/catch.hpp
)
