cmake_minimum_required(VERSION 3.24)

set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_BUILD_TYPE Release)

project(bcpu-lib LANGUAGES C CXX)

add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME} PRIVATE
	"sources/info_linux.cpp"
	"sources/info_nt.cpp"
	"sources/info_macos.cpp"
	"sources/info_android.cpp"
	"sources/lib_core.cpp"
)

include_directories(${PROJECT_NAME} PRIVATE
	"${CMAKE_SOURCE_DIR}/deps"
	$ENV{PATH}
)

set(CLI_VERSION "bcpu-cli")
set(UI_VERSION "bcpu-ui")

add_subdirectory("sources/cli")
#add_subdirectory("sources/ui")