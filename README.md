# Canadian Experience Animation Project

This project is an animation system built in C++ using wxWidgets, featuring a unique mechanical animation system. The project demonstrates object-oriented programming principles and animation techniques through interactive mechanical components.

## Features

The machine system includes:
- Crank mechanism
- Automated box opening animation
- Spring-loaded Sparty character with bounce physics
- Pulley system with variable speeds
- Cam-driven timing mechanisms
- Belt-driven connections between components
- Movable characters
- Key frames and animation wiht tweening
- Save and Loading of files

  Run the program and load in the file movie.anim to see a short animated movie

## Prerequisites

To build and run this project, you'll need:
- C++ compiler
- CMake (3.x or higher)
- wxWidgets library
- CLion IDE (recommended) or Visual Studio

## Building the Project

### Using CLion (Recommended)
1. Clone this repository
2. Open the project in CLion
3. Let CLion configure CMake
4. Click the Build button or use the Run configuration

### Using CMake manually
```bash
mkdir build
cd build
cmake ..
make  # on Mac/Linux
# or use generated Visual Studio solution on Windows


