# Falling Sand Simulator

This is a simple falling sand simulator written in C++ using the SFML library.

## Basic description
This simulator allows to simulate falling sand. You can left-click to place sand.
The basic controls allow to manipulate the experience. 
If you want to make the simulation faster or slower you can
play with the timePerFrame variable in the main.cpp file.
<br><br>
You can also change the size of the window and the grid 
with windowWidth, windowHeight, gridWidth and gridHeight.
The grid and window should have the same x and y size, 
also it should be a multiple of the window size, so there is no
gap between the grid and the window.

## How to build
1. Clone the repository
2. Install the SFML library
3. Run the following commands in the terminal:
```bash
cd FallingSandSim
mkdir build
cd build
cmake ..
make
```
4. Run the executable with `./FallingSandSim`


## Coming soon
- More particles like water, walls, fire, smoke, etc.
- Object-oriented refactoring
  - An OOP approach allows a better code organization 
and a more modular design.
  - Examples for some classes would be some particle 
classes, a grid class, a simulation class, etc.
- Performance improvements
  - The current implementation is not the most efficient
  - The simulation should also work for much larger grids