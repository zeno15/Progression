CMAKE_MINIMUM_REQUIRED(VERSION 2.6)


PROJECT(Progression)

SET(SFML_DIR "" CACHE STRING "Base directory for SFML")
SET(SFML_VER "" CACHE STRING "SFML Version")


if (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
		MESSAGE(STATUS "Clang system/compiler detected")
		IF (SFML_DIR STREQUAL "")
			SET(SFML_DIR "$ENV{HOME}/SFML/include")
		ENDIF()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

		SET(THIRD_PARTY_LIBS ${THIRD_PARTY_LIBS}
		  sfml-window
		  sfml-graphics
		  sfml-system
		)
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
		MESSAGE(STATUS "G++ system/compiler detected")
		IF (SFML_DIR STREQUAL "")
			SET(SFML_DIR "$ENV{HOME}/SFML/include")
		ENDIF()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

		SET(THIRD_PARTY_LIBS ${THIRD_PARTY_LIBS}
		  sfml-window-s-d
		  sfml-graphics-s-d
		  sfml-system-s-d
		  xcb
		  X11
		  GL
		  GLEW
		  freetype
		  dl
          Xrandr
		  udev
		  jpeg
		)
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "Intel")
		MESSAGE(STATUS "Intel system/compiler detected")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL ${MSVC})
	ADD_DEFINITIONS(-DSFML_STATIC)
	MESSAGE(STATUS "Windows system/compiler detected")
	IF (SFML_DIR STREQUAL "")
		SET(SFML_DIR "C:/Libraries/SFML-2.3.2")
		SET(SFML_VER "2.3.2")
	ENDIF()

	SET(THIRD_PARTY_LIBS ${THIRD_PARTY_LIBS}
	  sfml-main-d
	  sfml-window-s-d
	  sfml-graphics-s-d
	  sfml-system-s-d
	  opengl32
	  freetype
	  jpeg
	  winmm
	  gdi32
	)
endif()

INCLUDE(${CMAKE_SOURCE_DIR}/ProjectFiles.cmake)


# Currently always making static THIRD_PARTY_LIBS
set(LIBRARY_EXTENSION "${LIBRARY_EXTENSION}-s")

# Determine what type of library (Debug/Release) to build
if (NOT CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_BUILD_TYPE Debug)
    set(LIBRARY_EXTENSION "${LIBRARY_EXTENSION}-d")

else(NOT CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_BUILD_TYPE Release)

endif()

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include/)

MESSAGE(STATUS "SFML Version:" ${SFML_VER})
MESSAGE(STATUS "SFML Include Directory: " ${SFML_DIR}/include)
INCLUDE_DIRECTORIES(${SFML_DIR}/include)
MESSAGE(STATUS "SFML Link Directory: " ${SFML_DIR}/lib)
LINK_DIRECTORIES(${SFML_DIR}/lib)



# Create Local Libraries
ADD_LIBRARY(Progression${LIBRARY_EXTENSION} STATIC ${SOURCE_FILES} ${INCLUDE_FILES})


SET(LOCAL_LIBS ${LOCAL_LIBS}
	Progression${LIBRARY_EXTENSION}
)

SET(ALL_LIBS ${ALL_LIBS}
	${LOCAL_LIBS}
	${THIRD_PARTY_LIBS}
)

GET_DIRECTORY_PROPERTY( DirDefs DIRECTORY ${CMAKE_SOURCE_DIR} COMPILE_DEFINITIONS )
FOREACH( d ${DirDefs} )
    MESSAGE( STATUS "Definition: " ${d} )
ENDFOREACH()
FOREACH( l ${THIRD_PARTY_LIBS} )
    MESSAGE( STATUS "Third Party Library: " ${l} )
ENDFOREACH()
FOREACH( l ${LOCAL_LIBS} )
    MESSAGE( STATUS "Local Library: " ${l} )
ENDFOREACH()

ADD_EXECUTABLE(Main main.cpp)
TARGET_LINK_LIBRARIES(Main LINK_PUBLIC ${ALL_LIBS})

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/test/include)

ADD_EXECUTABLE(Test test/testMain.cpp ${TEST_SOURCE_FILES})
TARGET_LINK_LIBRARIES(Test LINK_PUBLIC ${ALL_LIBS})