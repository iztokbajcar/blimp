# Blimp
A simple 3D graphics engine.

## Prerequisites
To use the engine, you will need:  

- [GLEW](http://glew.sourceforge.net/)  
- [GLFW](http://www.glfw.org/)  
- [glm](https://github.com/g-truc/glm)  
- [SOIL](https://github.com/littlstar/soil)

To generate documentation and a simple demo, you will also need:  

- [Doxygen](https://www.doxygen.nl/)  
- [gcc](https://gcc.gnu.org/)  
- [Make](https://www.gnu.org/software/make/)  

On Linux, you can install these with your package manager.  

- using `apt`:  
```bash
apt-get install doxygen g++ libglew-dev libglfw3-dev libglm-dev libsoil-dev make
```  

- using `pacman`:  
```bash
pacman -S doxygen gcc glew glfw glm make soil
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
demo/bin/demo
```
