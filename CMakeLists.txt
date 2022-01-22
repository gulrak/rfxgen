cmake_minimum_required(VERSION 3.16)

project(rFXGen VERSION 3.0 LANGUAGES C CXX)

if(EMSCRIPTEN)
    set(PLATFORM "Web")
endif()

if(CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
    set(WITH_FLAT_OUTPUT ON CACHE BOOL "Build with collecting output directories bin&lib")

    include(cmake/CompilerOptions.cmake)

    include(FetchContent)
    FetchContent_Declare(
        raylib
        URL https://github.com/raysan5/raylib/archive/refs/tags/4.0.0.tar.gz
    )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED)
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
        add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
        include_directories(${raylib_SOURCE_DIR}/src/extras)
    endif()
endif()

add_executable(rfxgen src/rfxgen.c src/external/tinyfiledialogs.c src/random.c)
target_compile_definitions(rfxgen PRIVATE PORTABLE_RANDOM_GENERATOR)
target_link_libraries(rfxgen PRIVATE compiler_options raylib)
if (${PLATFORM} MATCHES "Web")
    set_target_properties(rfxgen PROPERTIES SUFFIX ".html")
endif ()