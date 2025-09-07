cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

#Setup
project(wx_cmake_fetchcontent_template LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Fetch Content
include(FetchContent)

#WxWidgets
set(wxBUILD_SHARED OFF)
message(STATUS "Fetching wxWidgets...")
FetchContent_Declare(
   wxWidgets
   GIT_REPOSITORY https://github.com/wxWidgets/wxWidgets.git
   GIT_SHALLOW ON
   SOURCE_DIR ${CMAKE_BINARY_DIR}/wxWidgets
)
FetchContent_MakeAvailable(wxWidgets)

#Adding Executable
file(GLOB SRC_FILES
     "src/*.hpp"
     "src/*.cpp"
)
if(APPLE)
    # create bundle on apple compiles
    add_executable(${PROJECT_NAME} MACOSX_BUNDLE ${SRC_FILES})

    # Set a custom plist file for the app bundle - needed for Mac OS Retina display.
    set_target_properties(main PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/Info.plist)
else()
    # the WIN32 is needed for Windows in order for it to look for WinMain.
    add_executable(${PROJECT_NAME} WIN32 ${SRC_FILES})
endif()

#Linking Libraries
target_link_libraries(${PROJECT_NAME} PRIVATE wxcore wxnet)
