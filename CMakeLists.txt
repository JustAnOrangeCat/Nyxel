cmake_minimum_required(VERSION 3.14)
project(Nyxel)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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
    GIT_TAG        3.0.0
)
FetchContent_MakeAvailable(SFML)

include_directories(imgui)

file(GLOB_RECURSE SRC_FILES

    "${CMAKE_SOURCE_DIR}/imgui/*.cpp"
    "${CMAKE_SOURCE_DIR}/imgui/*.h"


    "${CMAKE_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/*.h"
)

# Add your executable
add_executable(${PROJECT_NAME} ${SRC_FILES})

# Link SFML modules
target_link_libraries(${PROJECT_NAME}
    sfml-graphics
    sfml-window
    sfml-system
    stdc++fs
)

# On Windows, link additional system libraries for static SFML
if(WIN32)
    target_link_libraries(${PROJECT_NAME}
        opengl32
        gdi32
        winmm
        user32
        shell32
        imm32
    )
endif()
