cmake_minimum_required(VERSION 3.16.3)

project(
  unofficial-discord-client
  VERSION 0.1
  DESCRIPTION "Discord unofficial desktop application"
  LANGUAGES CXX)

option(EXTERNAL_OPUS "Use existing Opus library instead of building a private copy from the Opus submodule")
option(OPUS_PATH "Path to Opus library")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
# Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

if(EXTERNAL_OPUS)
    set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR/cmake/modules}")
    find_package(Opus)
else()
    add_subdirectory(opus)
endif()

if(MSVC)
  set(CMAKE_CXX_FLAGS "/W4 /wd4711 /wd4577 /experimental:external \
        /external:anglebrackets /external:W0")
else()
  set(CMAKE_CXX_FLAGS
      "-Wall -Wextra -Wpedantic -Wdouble-promotion -Wimplicit-fallthrough \
        -Winit-self -Wfloat-equal -Wformat=2 -Wmissing-include-dirs \
        -Wnull-dereference -Wshadow -Wstrict-overflow=5 -Wtautological-compare")
endif()

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_subdirectory(src)
