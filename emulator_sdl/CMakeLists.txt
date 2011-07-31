cmake_minimum_required (VERSION 2.6 FATAL_ERROR)
#set (CMAKE_VERBOSE_MAKEFILE ON)

# Program name
set (App_Name "emulator_sdl")
if (App_Name STREQUAL "")
	message (FATAL_ERROR "You must set the App_Name variable!")
endif ()

project (${App_Name})

################################################################################
# Ensure that we are not building in our source directories.

set (Build_Dir_OK "TRUE")
string (REGEX MATCH "^${CMAKE_SOURCE_DIR}" In_Sub_Dir ${CMAKE_BINARY_DIR})
if (In_Sub_Dir)
	string (REGEX MATCH "^${CMAKE_SOURCE_DIR}/build" In_Build_Dir ${CMAKE_BINARY_DIR})
	if (NOT In_Build_Dir)
		set (Build_Dir_OK "FALSE")
	endif ()
endif ()

if (NOT Build_Dir_OK)
	message (FATAL_ERROR "You must run cmake from a directory that is not in your source tree, or that is in a special subdirectory of the tree whose name begins with ‘build’.")
endif ()

file( MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/resources )
if (WIN32)
	file(COPY ${CMAKE_SOURCE_DIR}/resources/man_sprite.png DESTINATION ${CMAKE_BINARY_DIR}/resources/man.png)
else ()
	execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_SOURCE_DIR}/resources/man_sprite.png ${CMAKE_BINARY_DIR}/resources/man.png)
endif ()                                                
################################################################################
# Set up the basic build environment

if (CMAKE_BUILD_TYPE STREQUAL "")
	# CMake defaults to leaving CMAKE_BUILD_TYPE empty. This messes up
	# differentiation between debug and release builds.              
	set (CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif ()

################################################################################
# The core project files

file (GLOB SRCS src/*.cpp)
file (GLOB HDRS include/*.h include/*.hpp)

link_directories (
  )

include_directories (
  ${CMAKE_SOURCE_DIR}/include
  )

if (WIN32)
  add_executable (${App_Name} WIN32
    ${SRCS}
    ${HDRS}
    )
else ()
  add_executable (${App_Name}
    ${SRCS}
    ${HDRS}
    )
endif ()

target_link_libraries (${App_Name}
)

################################################################################
# SDL Support

# if (WIN32)
#   set (ENV{SDLDIR} "c:/gamedev/deps/sdl/SDL-build")
# else ()
#   set (ENV{SDLDIR} "/home/eris/gamedev/deps/sdl/SDL-build")
# endif ()


# SDL base package
# REQUIRED does not work in CMake <=2.4.6 for SDL
Find_Package ( SDL REQUIRED )
Find_Package ( SDL_image REQUIRED ) # if using SDL_image

if (NOT SDL_FOUND)
	message (FATAL_ERROR "SDL not found!")
endif (NOT SDL_FOUND)

include_directories(
	${SDL_INCLUDE_DIR}
	${INCLUDE_DIRECTORIES}
)
target_link_libraries(${App_Name}
	${SDL_LIBRARY}
	${SDLIMAGE_LIBRARY} # if using SDL_image, obviously
	${TARGET_LINK_LIBRARIES}
)
