#Project Fandral 

##Prerequisites
- Cmake
- Make or equivalent build tool
- g++
- Proper setup of wxWidgets library[Getting Started](https://wiki.wxwidgets.org/Getting_Started_with_wxWidgets)

Be sure to set the required make type by using -G flag in the cmake scripts.
eg: If i want unix makefiles: `cmake -G "Unix Makefiles"`

##For windows
-Check if WXWIN environment variable is properly set up: `%WXWIN%` should point to the wxWidget directory. If not then you can add a new environment variable named WXWIN and point towards wxWidgets directory.
-Uncomment the required lines in compile.bat script then `./compile.bat`

##For Uinux systems
-Check if  WX_CONFIG path is properly set up: `${WX_CONFIG}` should point to wx-config file.If not then you can find the path to wx-config (either in /usr/bin or /usr/local/bin depending upon your installation and might be in other places) and `export WX_CONFIG=path-to-wx-config`.
-Uncomment the required lines in compile.sh  script then `./compile.sh`

##Caveats
Sometimes even after proper compilation the applicaiton may not run saying it's missing library(windows) or some other error. To solve this, in windows you can register the dll or copy the missing dlls over to the build folder. In linux, the errors are other types of error which you might be able to solve by searching for particular distro or linux as general.

#Tldr
The application isn't complete, library isn't shipped along with it deal with the errors yourself, google is your friend.