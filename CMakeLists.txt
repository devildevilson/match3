# CMakeList.txt: проект CMake для match3; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

# Включение горячей перезагрузки для компиляторов MSVC, если поддерживается.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project(
  match3
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
endif()

include_directories(
  include/cosmojourney/include/dr_libs/
  include/cosmojourney/include/spdlog/include/
  include/cosmojourney/include/vorbis/include/
  include/cosmojourney/include/stb/
  include/cosmojourney/include/glm/
  include/cosmojourney/include/openal-soft/include
  include/cosmojourney/include/sml/include
  include/cosmojourney/include/qc-hash/
  include/cosmojourney/src/devils_engine/
  include/cosmojourney/src/cosmojourney/
  src/match3
)

add_subdirectory(include/cosmojourney/src/devils_engine/utils/)
add_subdirectory(include/cosmojourney/src/devils_engine/sound/)
add_subdirectory(include/cosmojourney/src/devils_engine/demiurg/)
add_subdirectory(src/match3/)

link_directories(libs)

# Добавьте источник в исполняемый файл этого проекта.
add_executable (${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} match3_core devils_utils devils_sound devils_demiurg)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
endif()