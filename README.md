# Conway's Game Of Life

## Implementation of the cellular automata simulation on C++, usign Piksel as the graphics library.

The Game of Life, is a cellular automaton created by John Conway in the 70's. It is meant to be a zero-player game, meaning that there is no interaction with the user other than the setup of the initial state. After that each iteration of the algorithm generates a new state based on the previous one according to a few rules:

* Any live cell with fewer than two neighbors dies, as if by underpopulation.
* Any live cell with two or three live neighbours lives on to the next generation.
* Any live cell with more than three live neighbours dies, as if by overpopulation.
* Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.

Given this simple set of rules, many different pattern of "living organisms" emerge such as:
#### Oscillators:
![Alt Text](https://upload.wikimedia.org/wikipedia/commons/9/95/Game_of_life_blinker.gif)
![Alt Text](https://upload.wikimedia.org/wikipedia/commons/1/12/Game_of_life_toad.gif)
![Alt Text](https://upload.wikimedia.org/wikipedia/commons/0/07/Game_of_life_pulsar.gif)

#### Spaceships:
![Alt Text](https://upload.wikimedia.org/wikipedia/commons/f/f2/Game_of_life_animated_glider.gif)
![Alt Text](https://upload.wikimedia.org/wikipedia/commons/3/37/Game_of_life_animated_LWSS.gif)

And more...

As of now, the project does not support loading a preset original mapping of the initial state from a file, but it will be added as soon as possible. 
Also, note that this project's purpose is practical learning of the C++ programming language, so I would not base your code on the one I push here. I will be refactoring and refining it on the following weeks but, until I am confident that the code here is up to a standard, I will keep this disclaimer here.
