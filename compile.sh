#!/bin/sh

#Uncomment the below two lines if running for the first time and replace MinGW Makefiles to whichever build generator you're using
#mkdir build
#MAKEFILE_TYPE="MinGW Makefiles"
#cmake -B ./build -S . -G "$MAKEFILE_TYPE"

cd build

cmake ../

cmake --build .

if [ $? ] 
then 
    ./Editor
else
    echo "Error occured during compilation. \n"
fi

cd ..
