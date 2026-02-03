#ifndef MAP_H
#define MAP_H

#include "player.h"

typedef enum
{
    STATE_2D,
    STATE_3D
} ViewMode;

#define TILE_SIZE 65

#define ROWS 14
#define COLUMNS 13

#define SCREEN_WIDTH (COLUMNS * TILE_SIZE)
#define SCREEN_HEIGHT (ROWS * TILE_SIZE)

#define MINIMAP_SCALE 0.2f

extern int WORLD_MAP[ROWS][COLUMNS];

void DrawMap(int mode);
void InitEditMap();

#endif