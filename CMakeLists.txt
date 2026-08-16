cmake_minimum_required(VERSION 3.20)

project(GMR LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/*.h"
)

add_executable(GMR ${SOURCES})

target_compile_features(GMR PRIVATE cxx_std_17)

target_compile_options(GMR PRIVATE
    /W4
    /EHsc
)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /MANIFEST:NO")