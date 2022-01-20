#! /bin/sh

#If building for the first time with minGw uncomment the following lines
#mkdir build
#makefile-type="MinGW Makefiles"
#cmake -B ./build -S . -G ${makefile-type}

#Changing to build directory
cd build

#Running cmake command there
cmake ../

#building the app and launching the app if the builing succeeds
cmake --build . && ./Editor

#Returning to project main directory
cd ..