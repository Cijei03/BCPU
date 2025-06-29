cmake_minimum_required(VERSION 3.24)

set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_BUILD_TYPE Release)

project(bcpu LANGUAGES C CXX)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
	"sources/app_core.cpp"
	"sources/info_linux.cpp"
)

target_include_directories(${PROJECT_NAME} PRIVATE 
	"${CMAKE_SOURCE_DIR}/deps"
)