set(CMAKE_SYSTEM_NAME "Android")
set(CMAKE_SYSTEM_PROCESSOR aarch64)

set(ANDROID_ABI arm64-v8a)
set(ANDROID_PLATFORM android-24)
include(/opt/android-ndk/build/cmake/android.toolchain.cmake)
add_compile_definitions(MOBILE_TARGET)