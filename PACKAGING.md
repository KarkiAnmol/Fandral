# Packaging
Packaging for .deb and .rpm packages are tested, others are untested.
You might be able ko use `cmake --install --prefix /usr/local/` to install the built packages, but this is not guarenteed.

## Building for release
`compile.sh -r -p /usr/local`

## Packaging

### For RPM
`cd build && cpack . -G RPM && cd ..`
### For Debian
`cd build && cpack . -G DEB && cd ..`

## Regarding installation_prefix
- Generally the installation_prefix for windows is 
{SystemDrive}\Program Files\{ProjectName}
- For GNU/Linux it is /usr or /usr/local
