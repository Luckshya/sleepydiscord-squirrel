cmake_minimum_required (VERSION 3.6)
project(sleepydiscord-squirrel)

option(BUILD_64 "" OFF)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include(ExternalProject)
include(buildtools/cmake/DownloadProject.cmake)

download_project(
	PROJ           sleepy-discord
	GIT_REPOSITORY https://github.com/yourWaifu/sleepy-discord.git
	GIT_TAG        develop
	SOURCE_DIR     ${PROJECT_SOURCE_DIR}/sleepy-discord
	UPDATE_DISCONNECTED 1
)
	
add_subdirectory(sleepy-discord)
add_subdirectory(src)