# MandelbrotViewerCPP

This repository is a C++ port of my [Mandelbrot Viewer Application](https://github.com/cianjinks/MandelbrotViewer) originally written in Java. It visualizes the Mandelbrot Set and allows for the panning and zooming of a camera to explore it. Maximum zoom capability is currently 64-bit.

Currently this version lacks ImGui implementation but otherwise is very similar.

## Download

Version 1.0 can be found on the releases tab in the form of an exe.

## Building from Source

**NOTE:** Currently only tested in Visual Studio 2019.

This program requires two dependencies to run:
* [GLAD with GL 4.6](https://glad.dav1d.de/) - includes
* [GLFW](https://www.glfw.org/download.html) - includes and static library