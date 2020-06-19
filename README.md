# MandelbrotViewerCPP

This repository is a C++ port of my [Mandelbrot Viewer Application](https://github.com/cianjinks/MandelbrotViewer) originally written in Java. It visualizes the Mandelbrot Set and allows for the panning and zooming of a camera to explore it. Maximum zoom capability is currently 64-bit.

Currently this version lacks ImGui implementation but otherwise is very similar.

## Download

Version 1.0 can be fonund on the releases tab.

## Building from Source

**NOTE:** Currently only tested in Visual Studio 2019.

To build from source you must include the include directories under "Dependencies/GLFW/x64/include" and "Dependencies/GLAD/include" as well as link the static libary "glfw3.lib" under "Dependencies/GLFW/x64/lib-vc2019/glfw3.lib". If you wish to run a 32-bit verison you can also include GLFW's x86 include folder.
