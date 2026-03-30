CMAKE_MINIMUM_REQUIRED(VERSION 3.30)

# Libraries linked via full path != linker search path error
CMAKE_POLICY(SET CMP0003 NEW)
# Removes unnecessary cmake files when generating MSVC project files
SET(CMAKE_SUPPRESS_REGENERATION TRUE)
# Link time optimizations
SET(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

SET(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_STANDARD_REQUIRED 20)

PROJECT("Learning Path Finding Algorithms"
    VERSION 0.0.1
    LANGUAGES CXX C
)

# Dependencies
INCLUDE(FetchContent)
SET(FETCHCONTENT_QUIET FALSE)

FetchContent_Declare(
    libfmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG 12.1.0
    GIT_PROGRESS TRUE
)

FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG "master"
    GIT_PROGRESS TRUE
)

FetchContent_MakeAvailable(libfmt raylib)

# App Executable
ADD_EXECUTABLE(app)

FILE(GLOB_RECURSE APP_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc")
FILE(GLOB_RECURSE APP_HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h")

TARGET_SOURCES(app PRIVATE
    ${APP_SOURCE_FILES}
    ${APP_HEADER_FILES}
)

TARGET_PRECOMPILE_HEADERS(app PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src/pch.h"
)

TARGET_INCLUDE_DIRECTORIES(app PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

TARGET_LINK_LIBRARIES(app PUBLIC
    fmt::fmt
    raylib
)

TARGET_COMPILE_DEFINITIONS(app PRIVATE
    ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/"
    _CRT_SECURE_NO_WARNINGS
)
