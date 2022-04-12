
cmake_minimum_required(VERSION 3.10)

#Required version of cpp
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#For getting absolute path to the project directory inside of the app
get_filename_component(PROJECT_ABSOLUTE_PATH "${PROJECT_DIR}" ABSOLUTE CACHE)

#set build type as debug
set(CMAKE_BUILD_TYPE Debug)
set(wxWidgets_CONFIGURATION mswud)

# set the project name
project("FandralEditor" VERSION 0.3 LANGUAGES CXX C)

# hack for buggy CMake's FindwxWidgets script
if (DEFINED ENV_WX_CONFIG)
    set (ENV{WX_CONFIG} ${ENV_WX_CONFIG})
endif()

#create a list to keep source files in a place
set(SRCS "src/App.cpp")

#append lists to add files for main window
list(APPEND SRCS "src/MainWindow.cpp")
list(APPEND SRCS "src/MyTab2.cpp")
list(APPEND SRCS "src/TextCtrl.cpp")
list(APPEND SRCS "src/ModifiedNotebook.cpp")
list(APPEND SRCS "src/CodeHighliter.cpp")
list(APPEND SRCS "src/CommandArea.cpp")

if (APPLE)
    # create bundle on apple compiles
    add_executable(${PROJECT_NAME} MACOSX_BUNDLE ${SRCS} )
    # Set a custom plist file for the app bundle - needed for Mac OS Retina display
    set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${PROJECT_DIR}/Info.plist)
else()
    # the WIN32 is needed for Windows in order for it to look for WinMain
    # instead of the main function. This is ignored on other systems,
    # so it works on all platforms
    add_executable(${PROJECT_NAME} WIN32 ${SRCS})
endif()

configure_file(include/AppConfig.h.in AppConfig.h)

target_include_directories("${PROJECT_NAME}" PUBLIC "${PROJECT_BINARY_DIR}" PUBLIC include)

find_package(wxWidgets REQUIRED gl aui core base stc html OPTIONAL_COMPONENTS net)

if(wxWidgets_FOUND)
    include(${wxWidgets_USE_FILE})
    #For building statically: target_link_libraries(${PROJECT_NAME}  "-static" ${wxWidgets_LIBRARIES})
    target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})
endif()
