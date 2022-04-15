#! /bin/sh

#If building for the first time,  uncomment the following lines
mkdir build
cmake -B ./build -S .

#Changing to build directory
cd build

#Running cmake command there
cmake ../

#building the app and launching the app if the builing succeeds
cmake --build . && ./FandralEditor

#Returning to project main directory
cd ..
