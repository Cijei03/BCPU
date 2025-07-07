set(CMAKE_SYSTEM_NAME "Android")
set(CMAKE_SYSTEM_PROCESSOR aarch64)

set(ANDROID_ABI arm64-v8a)
set(ANDROID_PLATFORM android-24)
include(/opt/android-ndk/build/cmake/android.toolchain.cmake)
#set(CMAKE_C_COMPILER /bin/arm-none-eabi-gcc)
#set(CMAKE_CXX_COMPILER /bin/arm-none-eabi-g++)

#add_compile_options(-march=armv8-a -static)
