cmake_minimum_required(VERSION 3.24)

set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_BUILD_TYPE Release)

set(CMAKE_HOST_SYSTEM_PROCESSOR ARM64)

project(bcpu LANGUAGES C CXX)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
	"sources/app_core.cpp"
	"sources/info_linux.cpp"
	"sources/info_winnt.cpp"
	"sources/info_macos.cpp"
)

target_include_directories(${PROJECT_NAME} PRIVATE 
	"${CMAKE_SOURCE_DIR}/deps"
	$ENV{PATH}
)

#add_compile_options(-target x86_64-pc-windows-gnu)
#add_compile_options(--target=armv7a-pc-windows)