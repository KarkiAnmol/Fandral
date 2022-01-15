@echo off
TITLE "Fandral Editor"

::Uncomment the below two lines if running for the first time replace MinGW Makefiles to whichever build generator you're using

    mkdir build
    set makefile-type="MinGW Makefiles"
    cmake -B ./build -S . -G %makefile-type%


::changing to build directory
cd build

::running cmake command there
cmake ../

::making the executables
cmake --build . && Editor

cd ..
