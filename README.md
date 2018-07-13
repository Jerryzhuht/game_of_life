# Game of Life

The Game of Life ([Wikipedia](https://en.wikipedia.org/wiki/Conway's_Game_of_Life)) is a simulation by British mathematician [J. H. Conway](http://conwaylife.com/) in 1970. The game models the life cycle of bacteria using a two-dimensional grid of cells. Given an initial pattern, the game simulates the birth and death of future generations of cells using a set of simple rules.

## Game of Life Simulation Rules:
Each grid location is either empty or occupied by a single living cell (X). A location's neighbors are any cells in the surrounding eight adjacent locations. In the example below, the shaded location has three neighbors containing living cells.

The Game of Life world is toroidal; this means that it wraps around in both dimensions. In other words, the top-most and bottom-most rows are considered to neighbor each other, as do the left-most and right-most columns. For example, the top-right X square in the example above has two neighbors that contain living cells: the cell down/left from it, and the cell up/right from it (which is the grid's bottom-left cell). To make sure that the definition of "neighbor" is well-defined, you may assume that the board's dimensions are at least 3x3.

The simulation starts with an initial pattern of cells on the grid and computes successive generations of cells according to the following rules:

* A location that has zero or one neighbors will be empty in the next generation. If a cell was there, it dies.
* A location with two neighbors is stable. If it had a cell, it still contains a cell. If it was empty, it's still empty.
* A location with three neighbors will contain a cell in the next generation. If it was unoccupied before, a new cell is born. If it currently contains a cell, the cell remains.
* A location with four or more neighbors will be empty in the next generation. If there was a cell in that location, it dies of overcrowding.
* The births and deaths that transform one generation to the next all take effect simultaneously. When you are computing a new generation, new births/deaths in that generation don't impact other cells in that generation. Any changes (births or deaths) in a given generation k start to have effect on other neighboring cells in generation k + 1.

## Input Files:
In each input file, the first two lines will contain integers r and c representing the number of rows and columns in the grid, respectively. The next lines of the file will contain the grid itself, a set of characters of size r x c with a line break (\n) after each row. Each grid character will be either a '-' (minus sign) for an empty dead cell, or an 'X' (uppercase X) for a living cell. The input file might contain additional lines of information after the grid lines, such as comments by its author or even junk/garbage data; any such content should be ignored by the program. We may assume that the world's size is at least 3x3.

## Build Project:
Use **Life.pro** to build.
