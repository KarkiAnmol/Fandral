#! /bin/sh

release='false'
debug='true'
local_install='false'
installation_prefix="/usr/local"
build_type='debug'
wx_widgets_configuration='msud'

print_usage() {
  printf "\nUsage: compile.sh \
  \n [ -d Debug build] \
  \n [ -r Release build] \
  \n [ -l local installation] \
  \n [ -p <path> installation prefix]
  \n"
}

# Taking the arguments with flags
while getopts 'drlp:' flag; do
  case "${flag}" in
    d) debug='true'
       release='false'
       build_type="debug"
       wx_widgets_configuration="msud" 
       ;;
    r) release='true'
       debug='false'
       build_type="release"
       wx_widgets_configuration="msu"
       ;;
    l) local_install='true'
       installation_prefix="./local_install"
       ;;
    p) installation_prefix="${OPTARG}"
       local_install='false'
       ;;
    *) print_usage
       exit 1 
       ;;
  esac
done

printf "\nThe input configuration \n debug: %s \n release: %s \n local_install: %s \n" \
     "${debug}" "${release}" "${local_install}"  

printf "Using the following: \n build_type: %s \n installation_prefix: %s \n wx_widgets_configuration: %s \n\n" \
     "${build_type}" "${installation_prefix}" "${wx_widgets_configuration}"


# working dir
cwd="$(pwd)"
printf "cwd: %s \n\n" "$cwd"

mkdir -p build

#Changing to build directory
cd build \
    &&
# Running cmake command there ( setting the DATA_DIR to the current location, as this makes easier for checking without installing)
# this should be removed during packaging
cmake -DCMAKE_INSTALL_PREFIX="${installation_prefix}" -DCMAKE_BUILD_TYPE="${build_type}" -DwxWidgets_CONFIGURATION="${wx_widgets_configuration}" -B . -S ../ \
    &&
#building the app and launching the app if the builing succeeds
cmake --build . && \
if [ ${local_install} = "true" ]; then  # installing if it is a local installation
    cmake --install . --prefix "${installation_prefix}" 
    ./FandralEditor 
fi \
    &&
#Returning to project main directory
cd ..
