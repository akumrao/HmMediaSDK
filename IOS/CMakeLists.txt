# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

set(CMAKE_CXX_STANDARD 14)	

cmake_minimum_required(VERSION 3.4.1)

set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER clang++)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(hmSdkUpload)


include_directories(./mediaserver/src/base/include ./mediaserver/src/net/src/net/awsupload/ ./mediaserver/src/http_parser ./mediaserver/src/crypto/include ./mediaserver/src/json/include ./mediaserver/src/net/include  ./mediaserver/src/libuv/include ./mediaserver/src/libuv/src ./mediaserver/src/libuv/src/unix )

file(GLOB SOURCES "Hm*.cpp"  "./mediaserver/src/libuv/src/*.cpp" "./mediaserver/src/base/src/*.cpp" "./mediaserver/src/net/src/TcpC*.cpp" "./mediaserver/src/net/src/U*.cpp" "./mediaserver/src/net/src/IP.cpp" "./mediaserver/src/net/awsupload/hm*Client.cpp"  )

list(APPEND SOURCES
       ./mediaserver/src/libuv/src/unix/async.cpp
       ./mediaserver/src/libuv/src/unix/core.cpp
       ./mediaserver/src/libuv/src/unix/dl.cpp
       ./mediaserver/src/libuv/src/unix/fs.cpp
       ./mediaserver/src/libuv/src/unix/getaddrinfo.cpp
       ./mediaserver/src/libuv/src/unix/getnameinfo.cpp
       ./mediaserver/src/libuv/src/unix/loop-watcher.cpp
       ./mediaserver/src/libuv/src/unix/loop.cpp
       ./mediaserver/src/libuv/src/unix/pipe.cpp
       ./mediaserver/src/libuv/src/unix/poll.cpp
       ./mediaserver/src/libuv/src/unix/process.cpp
       ./mediaserver/src/libuv/src/unix/random-devurandom.cpp
       ./mediaserver/src/libuv/src/unix/signal.cpp
       ./mediaserver/src/libuv/src/unix/stream.cpp
       ./mediaserver/src/libuv/src/unix/tcp.cpp
       ./mediaserver/src/libuv/src/unix/thread.cpp
       ./mediaserver/src/libuv/src/unix/tty.cpp
       ./mediaserver/src/libuv/src/unix/udp.cpp)


if(APPLE OR CMAKE_SYSTEM_NAME MATCHES "DragonFly|FreeBSD|NetBSD|OpenBSD")
  list(APPEND SOURCES ./mediaserver/src/libuv/src/unix/bsd-ifaddrs.cpp ./mediaserver/src/libuv/src/unix/kqueue.cpp)
endif()

if(APPLE OR CMAKE_SYSTEM_NAME MATCHES "Android|Linux|OS/390")
  list(APPEND SOURCES ./mediaserver/src/libuv/src/unix/proctitle.cpp)
endif()


if(APPLE OR CMAKE_SYSTEM_NAME STREQUAL "OpenBSD")
  list(APPEND SOURCES ./mediaserver/src/libuv/src/unix/random-getentropy.cpp)
endif()

if(APPLE)
  list(APPEND uv_defines _DARWIN_UNLIMITED_SELECT=1 _DARWIN_USE_64_BIT_INODE=1)
  list(APPEND SOURCES
       ./mediaserver/src/libuv/src/unix/darwin-proctitle.cpp
       ./mediaserver/src/libuv/src/unix/darwin.cpp
       ./mediaserver/src/libuv/src/unix/fsevents.cpp)
endif()


#
#file(GLOB SOURCES "*.cpp")

set (CMAKE_CXX_STANDARD 14)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
        hmSdkUpload

        # Sets the library as a shared library.
        STATIC

        # Provides a relative path to your source file(s).
        ${SOURCES})

target_compile_definitions(hmSdkUpload
                           PUBLIC ${uv_defines} )

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

#add_executable(hmSdkUpload main.cpp)

#target_link_libraries(native-lib )
