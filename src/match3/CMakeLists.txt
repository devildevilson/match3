cmake_minimum_required(VERSION 3.1...3.25)

set(GAME_LIBRARY_NAME match3_core)

project(
  ${GAME_LIBRARY_NAME}
  VERSION 0.1
  LANGUAGES CXX
)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  set(CMAKE_CXX_EXTENSIONS OFF)

  set_property(GLOBAL PROPERTY USE_FOLDERS ON)

  set(CMAKE_CXX_STANDARD 20)

  if (CMAKE_BUILD_TYPE STREQUAL "Debug")
	if(MSVC)
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /GR /Wall /permissive-")
    else()
	  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra")
    endif()
  endif()

  if (CMAKE_BUILD_TYPE STREQUAL "Release")
	if(MSVC)
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /O2 /permissive-")
    else()
	  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
    endif()
  endif()

  include_directories(
    include/dr_libs/
    include/spdlog/include/
    include/vorbis/include/
    include/stb/
    include/glm/
    include/openal-soft/include
    src/devils_engine/
  )
endif()

set(SRC_LIST
  simul_render.cpp
  simul_sound.cpp
  simul_world.cpp
)

set(HDR_LIST
  simul_interface.h
  simul_render.h
  simul_sound.h
  simul_world.h
)

add_library(${GAME_LIBRARY_NAME} ${SRC_LIST} ${HDR_LIST})
target_link_libraries(${GAME_LIBRARY_NAME} devils_utils devils_sound devils_demiurg)