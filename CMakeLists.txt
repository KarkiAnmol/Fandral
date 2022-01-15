
cmake_minimum_required(VERSION 3.10)

#Required version of cpp
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#set g++ as compiler
set(CMAKE_CXX_COMPILER g++)

# set the project name
project(Editor VERSION 0.1)

find_package(wxWidgets REQUIRED COMPONENTS core base net)
include(${wxWidgets_USE_FILE})

# add the executable
add_executable(Editor src/App.cpp)

target_link_libraries(Editor ${wxWidgets_LIBRARIES})