

## Dependencies
- SDL2
- fmt 

## Building and Running

CMake is used as the build system. First make sure you have all the libraries installed and accessable to CMake. This is a pain on windows, but easy on Linux.

When in the base directory of the repository run this: 

### Linux and MacOS


```
mkdir build
cd build
cmake .. 
make 
./codeeditor
```
There is also a bash build script which builds and runs it called `linux_build.sh`. This file needs permissions but it should execute all the commands above. 

### Windows

Windows is a bit more complex (Because of course it is...). 

If possible I recommend opening the base directory in Visual Studio
and letting it setup for CMake. This will output in and `out` folder by default. 

