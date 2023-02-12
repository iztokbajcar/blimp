# Blimp
A simple 3D graphics engine.

## Prerequisites
- [GLEW](http://glew.sourceforge.net/)
- [GLFW](http://www.glfw.org/)
- [glm](https://github.com/g-truc/glm)

To generate documentation and a simple demo, you will also need:
- [Doxygen](http://www.stack.nl/~dimitri/doxygen/)
- [gcc](https://gcc.gnu.org/)
- [Make](https://www.gnu.org/software/make/)

On Linux, you can install these with your package manager.
 - using `apt`:
```bash
apt-get install doxygen g++ libglew-dev libglfw3-dev libglm-dev make
```
 - using `pacman`:
```bash
pacman -S doxygen gcc glew glfw glm make
```

## Docs
To generate the documentation, run:
```bash
make docs
```

## Demo
To build and run the demo, run:
```bash
make demo
```