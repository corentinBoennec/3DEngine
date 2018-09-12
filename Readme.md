# 3DEngine

A small 3DEngine build with C++ and OpenGL.

## How to install

You need CMake and Visual Studio compiler (MSVC).

Step by step guide :

- Clone this reposatory
- Download freeglut 3.0.0 for MSVC [here](https://www.transmissionzero.co.uk/software/freeglut-devel/)
- Unzip freeglut and put it where you can find it easily
- Launch CMake, set the path of the project and the path of the build (create a folder outside the project's folder)
- Add the variable's path for GLUT (check grouped and advanced)
- Click on configure, then generate
- Add freeglut.dll (available in /bin) in your build folder
- Open the visual studio solution in build
- Here you go !