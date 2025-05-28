cmake_minimum_required(VERSION 3.14)
project(MySFMLProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory("src")

# Treat all libraries as static
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build static libraries")

# Add SFML_STATIC define so SFML uses static linking logic
add_compile_definitions(SFML_STATIC)

# Include FetchContent to handle external libraries
include(FetchContent)

# Set the base directory for external dependencies
set(FETCHCONTENT_BASE_DIR ${CMAKE_SOURCE_DIR}/external)

# Fetch SFML
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG        2.6.0
)
FetchContent_MakeAvailable(SFML)

file(GLOB_RECURSE SRC_FILES

    "${CMAKE_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/*.h"

)

# Add your executable
add_executable(MySFMLApp ${SRC_FILES})

# Link SFML modules
target_link_libraries(MySFMLApp
    sfml-graphics
    sfml-window
    sfml-system
)

# On Windows, link additional system libraries for static SFML
if(WIN32)
    target_link_libraries(MySFMLApp
        winmm
        gdi32
        opengl32
    )
endif()
