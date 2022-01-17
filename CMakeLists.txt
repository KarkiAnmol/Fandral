
cmake_minimum_required(VERSION 3.10)

#Required version of cpp
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#set g++ as compiler
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_BUILD_TYPE Debug)
set(wxWidgets_CONFIGURATION mswud)

# set the project name
project(Editor VERSION 0.1)

# add the executable
add_executable(${PROJECT_NAME} src/App.cpp)

#Uncomment this after you have found a way to include wxWidgets library
find_package(wxWidgets REQUIRED gl core base OPTIONAL_COMPONENTS net)

include(include/app.h ${wxWidgets_USE_FILE})
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})
