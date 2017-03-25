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
	${CMAKE_SOURCE_DIR}/include/Infrastructure/FontManager.hpp
	${CMAKE_SOURCE_DIR}/include/Infrastructure/InstanceCollection.hpp
	${CMAKE_SOURCE_DIR}/include/Infrastructure/Manager.hpp
	${CMAKE_SOURCE_DIR}/include/Infrastructure/Scene.hpp
	${CMAKE_SOURCE_DIR}/include/Infrastructure/SceneManager.hpp
	${CMAKE_SOURCE_DIR}/include/Infrastructure/ShaderManager.hpp
	${CMAKE_SOURCE_DIR}/include/Infrastructure/Signal.hpp
	${CMAKE_SOURCE_DIR}/include/Infrastructure/TextureManager.hpp
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


SET(INCLUDE_FILES ${INCLUDE_FILES}
	${ECS_INCLUDE_FILES}
	${GRAPHICS_INCLUDE_FILES}
	${INFRASTRUCTURE_INCLUDE_FILES}
	${SYSTEM_INCLUDE_FILES}
	${UTILITY_INCLUDE_FILES}
	${WINDOW_INCLUDE_FILES}
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

SET(SOURCE_FILES ${SOURCE_FILES}
	${ECS_SOURCE_FILES}
	${GRAPHICS_SOURCE_FILES}
	${INFRASTRUCTURE_SOURCE_FILES}
	${SYSTEM_SOURCE_FILES}
	${UTILITY_SOURCE_FILES}
	${WINDOW_SOURCE_FILES}
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
