
cmake_minimum_required(VERSION 3.10)

#Required version of cpp
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# set the project name
project("FandralEditor" VERSION 0.3 LANGUAGES CXX C)

# hack for buggy CMake's FindwxWidgets script
if (DEFINED ENV_WX_CONFIG)
    set (ENV{WX_CONFIG} ${ENV_WX_CONFIG})
endif()

message(STATUS "The build type is set as ${CMAKE_BUILD_TYPE}.")
#set build type as debug
if (NOT DEFINED CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(wxWidgets_CONFIGURATION mswud CACHE STRING "")

# the data directory
if (NOT DEFINED ENV{DATA_DIR})
    message(STATUS "Environment variable DATA_DIR not defined.")
    if (LINUX OR APPLE)
        set(DATA_DIR "${CMAKE_INSTALL_PREFIX}/share/${PROJECT_NAME}")
    elseif(WINDOWS)
        set(DATA_DIR "${CMAKE_INSTALL_PREFIX}")  # for windows, the default CMAKE_INSTALL_PREFIX is “<SystemDrive>/Program Files/<ProjectName>
    endif()
else()
    message(STATUS "Setting DATA_DIR to " $ENV{DATA_DIR} " as per the environment variable DATA_DIR")
    set(DATA_DIR $ENV{DATA_DIR})
endif()

if (DEFINED DATA_DIR AND NOT DEFINED ENV{DATA_DIR})
    message(STATUS "Setting DATA_DIR to " ${DATA_DIR} " as per default configuration.")
elseif(NOT DEFINED DATA_DIR)
    message(FATAL_ERROR "Default value for DATA_DIR not available.")
endif()

#create a list to keep source files in a place
set(SRCS "src/App.cpp")

#append lists to add source files
list(APPEND SRCS "src/MainWindow.cpp")
list(APPEND SRCS "src/MyTab2.cpp")
list(APPEND SRCS "src/TextCtrl.cpp")
list(APPEND SRCS "src/ModifiedNotebook.cpp")
list(APPEND SRCS "src/CodeHighliter.cpp")
list(APPEND SRCS "src/CommandArea.cpp")
list(APPEND SRCS "src/FindAndReplace.cpp")

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
    #For building statically: 
    #target_link_libraries(${PROJECT_NAME}  "-static" ${wxWidgets_LIBRARIES})
    
    # for building dynamically
    target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})
endif()

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin COMPONENT RUNTIME)
install(DIRECTORY resources DESTINATION ${DATA_DIR} USE_SOURCE_PERMISSIONS)  # copying the files under resources to DATA_DIR


# For packaging
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_VERSION_MAJOR ${FandralEditor_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${FandralEditor_VERSION_MINOR})
set(CPACK_PACKAGE_CONTACT "https://github.com/KarkiAnmol/Fandral")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libwxbase3.0-0v5(>= 3.0.5), libwxgtk3.0-gtk3-0v5(>=3.0.5), wx-common(>= 3.0.5)")

include(CPack)
