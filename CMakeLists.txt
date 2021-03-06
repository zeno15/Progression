CMAKE_MINIMUM_REQUIRED(VERSION 2.6)


PROJECT(Progression)

SET(FREETYPE_DIR "" CACHE STRING "Base directory for freetype")

if (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
		MESSAGE(STATUS "Clang system/compiler detected")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
		MESSAGE(STATUS "G++ system/compiler detected")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

		SET(THIRD_PARTY_LIBS ${THIRD_PARTY_LIBS}
#		  xcb
#		  X11
#		  GL
#		  GLEW
#		  freetype
#		  dl
#          Xrandr
#		  udev
#		  jpeg
		)
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "Intel")
		MESSAGE(STATUS "Intel system/compiler detected")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL ${MSVC})

	IF (FREETYPE_DIR STREQUAL "")
		SET(FREETYPE_DIR "C:/Libraries/freetype")
	ENDIF()

	ADD_DEFINITIONS(-DNOMINMAX -DWIN32_LEAN_AND_MEAN -D_CRT_SECURE_NO_DEPRECATE)

	SET(THIRD_PARTY_LIBS ${THIRD_PARTY_LIBS}
	  opengl32
	  winmm
	  gdi32
	  freetype
	)
endif()



# Currently always making static LOCAL_LIBS
set(LIBRARY_EXTENSION "${LIBRARY_EXTENSION}-s")

# Determine what type of library (Debug/Release) to build
if (NOT CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_BUILD_TYPE Debug)
    set(LIBRARY_EXTENSION "${LIBRARY_EXTENSION}-d")

else(NOT CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_BUILD_TYPE Release)

endif()

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include/)
INCLUDE_DIRECTORIES(${FREETYPE_DIR}/include/)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/thirdparty/)


LINK_DIRECTORIES(${FREETYPE_DIR}/lib)


INCLUDE(${CMAKE_SOURCE_DIR}/ProjectFiles.cmake)



# Create Local Libraries
ADD_LIBRARY(EntityComponentSystem${LIBRARY_EXTENSION}	STATIC ${ECS_SOURCE_FILES}					${ECS_INCLUDE_FILES})
ADD_LIBRARY(Infrastructure${LIBRARY_EXTENSION}			STATIC ${INFRASTRUCTURE_SOURCE_FILES}		${INFRASTRUCTURE_INCLUDE_FILES})
ADD_LIBRARY(Utility${LIBRARY_EXTENSION}					STATIC ${UTILITY_SOURCE_FILES}				${UTILITY_INCLUDE_FILES})

ADD_LIBRARY(Graphics${LIBRARY_EXTENSION}				STATIC ${GRAPHICS_SOURCE_FILES}				${GRAPHICS_INCLUDE_FILES})
ADD_LIBRARY(System${LIBRARY_EXTENSION}					STATIC ${SYSTEM_SOURCE_FILES}				${SYSTEM_INCLUDE_FILES})
ADD_LIBRARY(Window${LIBRARY_EXTENSION}					STATIC ${WINDOW_SOURCE_FILES}				${WINDOW_INCLUDE_FILES})

ADD_LIBRARY(Driller${LIBRARY_EXTENSION}					STATIC ${DRILLER_SOURCE_FILES}				${DRILLER_INCLUDE_FILES})
ADD_LIBRARY(Pong${LIBRARY_EXTENSION}					STATIC ${PONG_SOURCE_FILES}					${PONG_INCLUDE_FILES})



SET(LOCAL_LIBS ${LOCAL_LIBS}
	EntityComponentSystem${LIBRARY_EXTENSION}
	Infrastructure${LIBRARY_EXTENSION}
	Utility${LIBRARY_EXTENSION}
	
	Graphics${LIBRARY_EXTENSION}
	System${LIBRARY_EXTENSION}
	Window${LIBRARY_EXTENSION}

	Driller${LIBRARY_EXTENSION}	
	Pong${LIBRARY_EXTENSION}
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