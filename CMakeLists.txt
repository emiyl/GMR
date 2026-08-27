cmake_minimum_required(VERSION 3.20)

project(GMR LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE GMR_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cxx"
)

add_executable(GMR ${GMR_SOURCES})

target_compile_features(GMR PRIVATE cxx_std_17)

target_compile_options(GMR PRIVATE
    /W4
    /EHsc
)

target_link_libraries(GMR PRIVATE winmm avrt)
target_link_options(GMR PRIVATE "/SUBSYSTEM:WINDOWS")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /MANIFEST:NO")