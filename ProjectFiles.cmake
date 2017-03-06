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
	${CMAKE_SOURCE_DIR}/include/Infrastructure/InstanceCollection.hpp
	${CMAKE_SOURCE_DIR}/include/Infrastructure/Manager.hpp
)

SET(INCLUDE_FILES ${INCLUDE_FILES}
	${ECS_INCLUDE_FILES}
	${INFRASTRUCTURE_INCLUDE_FILES}
)



# Source files
SET(ECS_SOURCE_FILES ${ECS_SOURCE_FILES}
	${CMAKE_SOURCE_DIR}/src/ECS/Component.cpp
	${CMAKE_SOURCE_DIR}/src/ECS/EntityManager.cpp
)

SET (INFRASTRUCTURE_TEST_SOURCE_FILES ${INFRASTRUCTURE_TEST_SOURCE_FILES}
	${CMAKE_SOURCE_DIR}/src/Infrastructure/InstanceCollection.cpp
)

SET(SOURCE_FILES ${SOURCE_FILES}
	${ECS_SOURCE_FILES}
	${INFRASTRUCTURE_TEST_SOURCE_FILES}
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
)

SET(TEST_SOURCE_FILES ${TEST_SOURCE_FILES}
	${ECS_TEST_SOURCE_FILES}
	${INFRASTRUCTURE_TEST_SOURCE_FILES}
)
