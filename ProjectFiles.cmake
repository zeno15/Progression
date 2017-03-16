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

SET(INFRASTRUCTURE_INCLUDE_FILES ${INFRASTRUCTURE_INCLUDE_FILES}
	${CMAKE_SOURCE_DIR}/include/Infrastructure/FontManager.hpp
	${CMAKE_SOURCE_DIR}/include/Infrastructure/InstanceCollection.hpp
	${CMAKE_SOURCE_DIR}/include/Infrastructure/Manager.hpp
	${CMAKE_SOURCE_DIR}/include/Infrastructure/Scene.hpp
	${CMAKE_SOURCE_DIR}/include/Infrastructure/SceneManager.hpp
	${CMAKE_SOURCE_DIR}/include/Infrastructure/TextureManager.hpp
)

SET(UTILITY_INCLUDE_FILES ${UTILITY_INCLUDE_FILES}
	${CMAKE_SOURCE_DIR}/include/Utility/StringHelper.hpp
	${CMAKE_SOURCE_DIR}/include/Utility/XML.hpp
)

SET(INCLUDE_FILES ${INCLUDE_FILES}
	${ECS_INCLUDE_FILES}
	${INFRASTRUCTURE_INCLUDE_FILES}
	${UTILITY_INCLUDE_FILES}
)



# Source files
SET(ECS_SOURCE_FILES ${ECS_SOURCE_FILES}
	${CMAKE_SOURCE_DIR}/src/ECS/Component.cpp
	${CMAKE_SOURCE_DIR}/src/ECS/EntityManager.cpp
)

SET (INFRASTRUCTURE_SOURCE_FILES ${INFRASTRUCTURE_SOURCE_FILES}
	${CMAKE_SOURCE_DIR}/src/Infrastructure/FontManager.cpp
	${CMAKE_SOURCE_DIR}/src/Infrastructure/InstanceCollection.cpp
	${CMAKE_SOURCE_DIR}/src/Infrastructure/Scene.cpp
	${CMAKE_SOURCE_DIR}/src/Infrastructure/SceneManager.cpp
	${CMAKE_SOURCE_DIR}/src/Infrastructure/TextureManager.cpp
)

SET(UTILITY_SOURCE_FILES ${UTILITY_SOURCE_FILES}
	${CMAKE_SOURCE_DIR}/src/Utility/StringHelper.cpp
	${CMAKE_SOURCE_DIR}/src/Utility/XML.cpp
)

SET(SOURCE_FILES ${SOURCE_FILES}
	${ECS_SOURCE_FILES}
	${INFRASTRUCTURE_SOURCE_FILES}
	${UTILITY_SOURCE_FILES}
)


# Test files
SET(ECS_TEST_SOURCE_FILES ${ECS_TEST_SOURCE_FILES}
	${CMAKE_SOURCE_DIR}/test/ECS/EntityTests.cpp
	${CMAKE_SOURCE_DIR}/test/ECS/EntityManagerTests.cpp
	${CMAKE_SOURCE_DIR}/test/ECS/ComponentTests.cpp
	${CMAKE_SOURCE_DIR}/test/ECS/SystemTests.cpp
)

SET (INFRASTRUCTURE_TEST_SOURCE_FILES ${INFRASTRUCTURE_TEST_SOURCE_FILES}
	${CMAKE_SOURCE_DIR}/test/Infrastructure/InstanceCollectionTests.cpp
	${CMAKE_SOURCE_DIR}/test/Infrastructure/SceneTests.cpp
	${CMAKE_SOURCE_DIR}/test/Infrastructure/SceneManagerTests.cpp
)

SET (UTILITY_TEST_SOURCE_FILES ${UTILITY_TEST_SOURCE_FILES}
	${CMAKE_SOURCE_DIR}/test/Utility/StringHelperTests.cpp
	${CMAKE_SOURCE_DIR}/test/Utility/XMLTests.cpp
)

SET(TEST_SOURCE_FILES ${TEST_SOURCE_FILES}
	${ECS_TEST_SOURCE_FILES}
	${INFRASTRUCTURE_TEST_SOURCE_FILES}
	${UTILITY_TEST_SOURCE_FILES}
)

SET(TEST_INCLUDE_FILES ${TEST_INCLUDE_FILES}
	${CMAKE_SOURCE_DIR}/test/include/catch.hpp
)
