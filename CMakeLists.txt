
cmake_minimum_required(VERSION 3.10)

#Required version of cpp
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#set g++ as compiler
set(CMAKE_CXX_COMPILER g++)

#set build type as debug
set(CMAKE_BUILD_TYPE Debug)
set(wxWidgets_CONFIGURATION mswud)

# set the project name
project(Editor VERSION 0.1)

#create a list to keep source files in a place
set(SRCS "src/App.cpp")

#append lists to add files for main window
list(APPEND SRCS "src/MainWindow.cpp")  

# add the executable
add_executable(${PROJECT_NAME} ${SRCS})

configure_file(include/AppConfig.h.in AppConfig.h)

target_include_directories("${PROJECT_NAME}" PUBLIC "${PROJECT_BINARY_DIR}" PUBLIC include)

#Uncomment this after you have found a way to include wxWidgets library
find_package(wxWidgets REQUIRED gl core base OPTIONAL_COMPONENTS net)

include(${wxWidgets_USE_FILE})

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})
