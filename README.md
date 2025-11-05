## to compile use :

## gcc *.c -Lminilibx -lmlx -lXext -lX11 -lm -o cub3d

# cub3D

A 3D maze game inspired by the classic Wolfenstein 3D, built using raycasting techniques.

## Description

cub3D is a project from the 42 school curriculum that introduces raycasting principles. The goal is to create a dynamic view inside a maze where you can navigate using a first-person perspective. This project uses the MiniLibX graphics library to render the 3D projection of a 2D map.

## Features

- **Raycasting engine**: Real-time 3D rendering using raycasting algorithms
- **Textured walls**: Different textures for each cardinal direction (North, South, East, West)
- **Floor and ceiling colors**: Customizable colors for floor and ceiling
- **Smooth navigation**: Move through the maze using keyboard controls
- **Collision detection**: Prevents walking through walls
- **Minimap** (bonus): Visual representation of the map and player position

## Installation

### Prerequisites

- GCC compiler
- Make
- MiniLibX library
- Linux or macOS

### Building the Project

```bash
# Clone the repository
git clone https://github.com/Assanfakou/game
cd game

# Compile the project
make

## Usage

```bash
./cub [path/to/map.cub]
```

### Example

```bash
./cub maps/example.cub
```

## Map Configuration

Maps are defined in `.cub` files with the following format:

```
NO ./textures/north_texture.xpm
SO ./textures/south_texture.xpm
WE ./textures/west_texture.xpm
EA ./textures/east_texture.xpm

F 220,100,0
C 225,30,0

1111111111111111111111111
1000000000110000000000001
1011000001110000000000001
1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```

### Map Elements

- `1`: Wall
- `0`: Empty space
- `N`, `S`, `E`, `W`: Player start position and orientation
- `NO`, `SO`, `WE`, `EA`: Path to wall textures
- `F`: Floor color (R,G,B)
- `C`: Ceiling color (R,G,B)

## Controls

### Mandatory

- `W` / `↑`: Move forward
- `S` / `↓`: Move backward
- `A`: Rotate camera left 
- `D`: Rotate camera right
- `←`: Rotate camera left
- `→`: Rotate camera right
- `ESC`: Exit the game

### Bonus

- `M`: Lunch the mini map
- `N`: Close the mini map

## Technical Concepts

### Raycasting

Raycasting is a rendering technique that creates a 3D perspective in a 2D map by:
1. Casting rays from the player's position
2. Calculating the distance to the nearest wall
3. Drawing vertical lines proportional to the distance
4. Applying textures based on wall orientation

### DDA Algorithm

The Digital Differential Analysis (DDA) algorithm is used to efficiently trace rays through the grid-based map to detect wall collisions.

## Bonus Features

- Minimap display
- Wall collisions

## Project Structure


## Error Handling

The program handles various error cases:
- Invalid map configuration
- Missing textures or invalid paths
- Invalid color values
- Map not surrounded by walls
- Multiple player positions
- Invalid characters in map

## Authors

[Laila Zari] - [lzari] 
[Hassan Fakou] - [hfakou] 

## License

This project is part of the 42 school curriculum.

##  Acknowledgments

- 42 Network for the project subject
- Wolfenstein 3D for the inspiration
- Lode Vandevenne's raycasting tutorial

## Resources

- [Lode's Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html)
- [Ray-Casting Tutorial For Game Development](https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/)
- [MiniLibX Documentation](https://harm-smits.github.io/42docs/libs/minilibx)