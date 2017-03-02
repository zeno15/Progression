CMAKE_MINIMUM_REQUIRED(VERSION 2.6)


PROJECT(Progression)

IF (WIN32)
ELSE()
  IF (APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
  ELSE()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
  ENDIF()
ENDIF()


SET(INCLUDE_FILES ${INCLUDE_FILES}
  ${CMAKE_SOURCE_DIR}/include/Progression/Factorial.hpp

  ${CMAKE_SOURCE_DIR}/include/ECS/Component.hpp
  ${CMAKE_SOURCE_DIR}/include/ECS/Entity.hpp
)

SET(SOURCE_FILES ${SOURCE_FILES}
  ${CMAKE_SOURCE_DIR}/src/Progression/Factorial.cpp

  ${CMAKE_SOURCE_DIR}/src/ECS/Component.cpp
)

SET(TEST_SOURCE_FILES ${TEST_SOURCE_FILES}
  ${CMAKE_SOURCE_DIR}/test/factorialTest.cpp

  ${CMAKE_SOURCE_DIR}/test/ECS/EntityTests.cpp
  ${CMAKE_SOURCE_DIR}/test/ECS/ComponentTests.cpp
)

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include)

ADD_LIBRARY(Progression-s STATIC ${SOURCE_FILES} ${INCLUDE_FILES})

ADD_EXECUTABLE(Main main.cpp)
TARGET_LINK_LIBRARIES(Main LINK_PUBLIC Progression-s)

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/test/include)

ADD_EXECUTABLE(Test test/testMain.cpp ${TEST_SOURCE_FILES})
TARGET_LINK_LIBRARIES(Test LINK_PUBLIC Progression-s)