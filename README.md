
## Dependencies

- GLFW
- fmt

## Cloning

To clone the repo: 
```
git clone --recursive https://github.com/Progalt/CodeEditor.git
```

then run: 
```
git submodule update --init --recursive
```
This will update all submodules recursively. It may take a while but thats normal. 

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

### Windows

Windows is a bit more complex (Because of course it is...). 

If possible I recommend opening the base directory in Visual Studio
and letting it setup for CMake. This will output in and `out` folder by default. 

Or: 

```
mkdir build
cd build
cmake ..
```
You should now have a Visual Studio solution to build. 