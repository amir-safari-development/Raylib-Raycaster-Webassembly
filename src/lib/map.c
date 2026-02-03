#include "map.h"
#include "player.h"

int WORLD_MAP[ROWS][COLUMNS] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

void DrawMap(int mode)
{
    int map_x = player.pos.x / TILE_SIZE;
    int map_y = player.pos.y / TILE_SIZE;

    float scale = mode == STATE_2D ? 1 : MINIMAP_SCALE;

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            Color cellColor;

            if (WORLD_MAP[i][j] == 1)
                cellColor = BLACK;
            else if (i == map_y && j == map_x)
                cellColor = LIGHTGRAY;
            else if (WORLD_MAP[i][j] == 0)
                cellColor = WHITE;

            DrawRectangle(j * TILE_SIZE * scale + (SCREEN_WIDTH - COLUMNS * TILE_SIZE * scale), i * TILE_SIZE * scale, TILE_SIZE * scale, TILE_SIZE * scale, cellColor);
            DrawRectangleLines(j * TILE_SIZE * scale + (SCREEN_WIDTH - COLUMNS * TILE_SIZE * scale), i * TILE_SIZE * scale, TILE_SIZE * scale, TILE_SIZE * scale, GRAY);
        }
    }
}

void InitEditMap()
{
    if (!((int)(GetMouseX() / TILE_SIZE) == (int)(player.pos.x / TILE_SIZE) && (int)(GetMouseY() / TILE_SIZE) == (int)(player.pos.y / TILE_SIZE)))
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            WORLD_MAP[(int)(GetMouseY() / TILE_SIZE)][(int)(GetMouseX() / TILE_SIZE)] = 1;

        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
            WORLD_MAP[(int)(GetMouseY() / TILE_SIZE)][(int)(GetMouseX() / TILE_SIZE)] = 0;
    }
}