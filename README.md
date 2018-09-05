# RT

RT is a 42 school project.
It's a program that render image using the [Ray Tracing](https://en.wikipedia.org/wiki/Ray_tracing_(graphics)) technique.
It is written in C, use the [SDL](https://www.libsdl.org) library for the display,
and the [OpenCL](https://www.khronos.org/opencl/) framework for computing performance.
The subject of the project can be find [here](./rt.en.pdf) (french version [here](./rt.fr.pdf)).

#### Features
The following features have been added to the project:
* .json file parsing for the scene description file (the parser can be found [here](https://github.com/MisterPeModder/ft_json)),
* GPU processing threw the OpenCL API,
* Intersection with basic objects (sphere, cylinder, cone, plane, triangle, disk, cube, paraboloid),
* Lights and shadows,
* Optional .obj file parsing for complex objects,
* Reflection and Refraction properties,
* Procedural Perturbation of the color or the surface of an object,
* Ray teleportation threw portals,
* Multi Sampling algorithm for anti aliasing,
* Timer for the process time,
* Joy-con support.

---
### Requirement

In order to use the program, you must have:
* a MacOS system,
* the Make software,
* the clang compiler,
* Several dependencies of the SDL library, such as freetype2 (the missing dependencies should be listed when compiling the program).

In order to compile the program, just use the commande `make` in the project directory.

---
### How to use RT ?
#### Launch the program

the command `./rt` show you a basic usage of the program. You must use the command with the path or a scene file as argument.
For example:

`./rt scenes/jhache.json`

This command will launch the "jhache" scene and generate a rendered view of it in a new window.

You can find several scene files in the `scenes` directory, and you can edit them as you want ([How to write a scene file ?](./scenes/README.md)).

#### Guide

Here is the list of the keys to interact with the program during its execution:
* W, S, A, D, SHIFT and SPACE for camera translation on the Z, X and Y axis (respectively),
* Up, Down, Left, Right, PageUp and PageDown for camera rotation on the X, Y and Z axis (respectively),
* (alphanumerical) + or - for changing the number of sample for multisampling,
* (alphanumerical) 0 to 6 to change the color filter,
* (numeric pad) + or - for changing the number of ray bounces,
* P for saving a screenshot in ppm format,
* ESC to quit the program.
