#!/bin/bash
export LD_LIBRARY_PATH="$PWD/vendor/lib/openal/lib:$LD_LIBRARY_PATH"
make bonus && ./cub3D_bonus map/GOT3D.cub