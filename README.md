# cub3D (42)

## Description

`cub3D` is a small Wolfenstein-style 3D engine written in C for the 42 curriculum.
It renders a 2D `.cub` map in first-person view with raycasting, wall textures, floor/ceiling colors (mandatory), and an extended bonus mode with gameplay/UI systems.

This README is based on the repository source code and build files only.

## Features

### Mandatory (`cub3D`)

- Raycasting renderer (DDA-based) for textured walls.
- Floor and ceiling color parsing from RGB values.
- `.cub` parsing with map validation (file extension, texture declarations, RGB format, closed map, player spawn rules).
- Player movement and rotation (`WASD` + arrow keys).
- Collision-aware movement.
- Crosshair rendering.

### Bonus (`cub3D_bonus`)

- Minimap rendering.
- Mouse look.
- Door system (`P` tiles in map, open/close logic).
- Enemy/bot spawning and update loop (`B` tiles in map).
- Weapon animation and shooting flow.
- Health bar, damage overlay, and menu states.
- Animated ceiling/loading assets.
- Sound effects and background music via `miniaudio`.

## How It Works

1. The parser reads the `.cub` file, validates identifiers and map integrity, and initializes runtime structures.
2. The game loop casts one ray per screen column, performs DDA traversal on the grid map, computes wall distances, and samples texture pixels.
3. Input flags are updated on key/mouse events, then consumed each frame to move/rotate the player with collision checks.
4. Bonus mode extends the same loop with minimap, doors, bots, menu, gun animation, and sound playback.

## Installation / Build

### Prerequisites

- Linux environment (project links against MiniLibX with X11).
- C compiler (`cc`).
- `make`.

### Build commands

```bash
# mandatory target
make

# bonus target
make bonus
```

Binary outputs:

- `./cub3D`
- `./cub3D_bonus`

## Usage

```bash
# mandatory
./cub3D map/test.cub

# bonus
./cub3D_bonus map/GOT3D.cub
```

Helper script:

```bash
./run.sh
```

### Controls

Mandatory:

- `W/A/S/D`: move
- `Left/Right`: rotate camera
- `Esc`: quit

Bonus (in addition):

- Mouse movement: camera rotation
- Left click: shoot
- `E`: interact with door
- `P`: open the pause menu during gameplay
- `Up/Down` + `Enter`: navigate/select when a menu is open

## Example

```bash
make bonus
./cub3D_bonus map/GOT3D.cub
```

This launches the extended mode map with doors, bots, minimap, HUD, and audio enabled by the current build.

## Project Structure

```text
.
├── include/           # headers (mandatory + bonus)
├── src/               # mandatory implementation
│   ├── parsing/
│   ├── draw/
│   ├── player/
│   ├── key/
│   ├── init/
│   └── error/
├── src_bonus/         # bonus implementation
│   ├── parsing/
│   ├── draw/
│   ├── bot/
│   ├── minimap/
│   ├── sound/
│   ├── key/
│   ├── init/
│   └── error/
├── map/               # sample .cub maps
├── textures/          # xpm texture assets / animations
├── sfx/               # audio assets (bonus)
├── libft/             # 42 libft dependency
├── mlx/               # MiniLibX
└── Makefile
```

## What I Learned

- Building a full render loop around raycasting and DDA traversal.
- Designing a strict parser/validator for configuration and map files.
- Managing real-time input, collisions, and frame-driven state updates.
- Structuring a C project across mandatory and bonus feature sets.
- Extending a renderer with gameplay systems (AI, doors, UI, audio) while preserving core architecture.
