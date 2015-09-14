# Oglu library 
 - version: 0.0.0

# Requierements
 - a C++ compiler with a good C++11 support
 - [CMake](http://www.cmake.org/)
 - [Boost](http://www.boost.org/) test framework (optional)
Notes only boost_test_unit_framework and boost_system are needed.
 - [Doxygen](http://www.stack.nl/~dimitri/doxygen/) (optional)
 - [OpenGL](https://www.opengl.org/)
 - [Glew](http://glew.sourceforge.net/)

Just install each programs/libraries required and cmake will
finds automaticly their locations.

Oglu example require OpenGL 4.1.  

# Submodules
Oglu use git submodule for somes of their dependencies.  
Don't forget to update these submodule by typing:

    git submodule update

# Building the project and compiling

    cd <where you want to build this project>
    cmake <path to this repository> -G "Unix Makefiles" -DBUILD_ALL=TRUE
    # make all...
    make
    # run the tests...
    ctest

You can also use ccmake if you want to configure the build more precisely or
to explore all the options availables.

## Build results location
All output are located at `<where you want to build this project>/output`.  

## CMake variables
Several CMake variable are defined.  
You can set variables with the flag -D (see example above and CMake documentation).  

 - BUILD_ALL (default FALSE):
Enable all build options.

 - BUILD_DOCUMENTATION (default TRUE): Build the library documentation.  
This option require Doxygen if enabled.  
The documentation will be builded in `<where you want to build this project>/output/html/`.

 - BUILD_TESTING (default TRUE):
Builds all unit tests program.  
To add a new test file, put your cpp in `tests/src/` directory then append the new path to the list of source in `tests/CMakeLists.txt`.  
Each test is generated in his own direction in `<where you want to build this project>/output/tests/`.  

