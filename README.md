# Falling Sand Simulator

This is a simple falling sand simulator written in C++ using the SFML library for the HWR course "CPP Programming".

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
2. Build the project using the CMake file
3. Run the following commands in the terminal:
```bash
coming soon
```
4. Run the executable with `./FallingSandSim`

## Inspirations
https://www.youtube.com/watch?v=L4u7Zy_b868 - This youtube video by "The Coding Train"
inspired me for this project. It was the first time i got into this concept of Cellular Automata.
The author explains the concept and the way of working very clearly.

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
- Option to rezise the window
  - The grid should rezise with the window
