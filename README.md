# simple_snake

simple snake game using sdl2.

# build on linux
make sure to install sdl2 and cmake according to your distribution
sdl2 works out of the box on linux
to compile this program
- create build directory (mkdir build)
- go inside and run root cmake text file (cd build; cmake ..)
- compile using gcc (make)

# build on windows
on windows you can use mingw or visual c++ compiler
you need to download sdl2 development version accordingly and link it to your project
I have provided 64 bit mingw version and visual c++ version in 'external' directory
you can change CMakeLists.txt to use either one, or modify so it will work in IDE
don't forget to copy sdl2.dll file in your executable's directory 
