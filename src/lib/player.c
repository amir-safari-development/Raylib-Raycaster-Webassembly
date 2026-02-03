#include "player.h"
#include <stdio.h>

Player player = {{}, {1, 0}, {0, 0.66}};

int sign(float x)
{
    return (x > 0) - (x < 0);
}

void PlacePlayer()
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            if (WORLD_MAP[i][j] == 0)
            {
                player.pos.x = j * TILE_SIZE + PLAYER_RADIUS;
                player.pos.y = i * TILE_SIZE + PLAYER_RADIUS;
                return;
            }
        }
    }
}

void DrawPlayer(int mode)
{
    float scale = mode == STATE_2D ? 1 : MINIMAP_SCALE;

    DrawCircle(player.pos.x * scale + (SCREEN_WIDTH - COLUMNS * TILE_SIZE * scale), player.pos.y * scale, PLAYER_RADIUS * scale, RED);
    DrawLine(player.pos.x * scale + (SCREEN_WIDTH - COLUMNS * TILE_SIZE * scale), player.pos.y * scale,
             player.pos.x * scale + (SCREEN_WIDTH - COLUMNS * TILE_SIZE * scale) + player.dir.x * 35 * scale,
             (player.pos.y + player.dir.y * 35) * scale, RED);
}

void CastRays(int x)
{
    double cameraX = 2.0 * x / (double)SCREEN_WIDTH - 1,
           rayDirX = player.dir.x + player.plane.x * cameraX,
           rayDirY = player.dir.y + player.plane.y * cameraX;

    double posX = player.pos.x / TILE_SIZE,
           posY = player.pos.y / TILE_SIZE;

    int mapX = (int)posX,
        mapY = (int)posY;

    double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX),
           deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);

    double sideDistX, sideDistY;
    int stepX, stepY;

    if (rayDirX < 0)
    {
        stepX = -1;
        sideDistX = (posX - mapX) * deltaDistX;
    }
    else
    {
        stepX = 1;
        sideDistX = (mapX + 1.0 - posX) * deltaDistX;
    }

    if (rayDirY < 0)
    {
        stepY = -1;
        sideDistY = (posY - mapY) * deltaDistY;
    }
    else
    {
        stepY = 1;
        sideDistY = (mapY + 1.0 - posY) * deltaDistY;
    }

    int hit = 0, side;
    while (hit == 0)
    {
        if (sideDistX < sideDistY)
        {
            sideDistX += deltaDistX;
            mapX += stepX;
            side = 0;
        }
        else
        {
            sideDistY += deltaDistY;
            mapY += stepY;
            side = 1;
        }

        if (mapX >= 0 && mapX < COLUMNS && mapY >= 0 && mapY < ROWS)
        {
            if (WORLD_MAP[mapY][mapX] == 1)
                hit = 1;
        }
        else
            break;
    }

    double perpWallDist = (side == 0) ? (sideDistX - deltaDistX) : (sideDistY - deltaDistY);
    if (perpWallDist <= 0)
        perpWallDist = 0.001;

    double distToProjPlane = (SCREEN_WIDTH / 2.0) / FOV_SCALE;

    int lineHeight = (int)(distToProjPlane / perpWallDist),
        drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2,
        drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;

    if (drawStart < 0)
        drawStart = 0;
    if (drawEnd >= SCREEN_HEIGHT)
        drawEnd = SCREEN_HEIGHT - 1;

    DrawLine(x, drawStart, x, drawEnd, (side == 1) ? ColorBrightness(BLACK, 0.2f) : BLACK);
}

void InitMobility(float moveSpeed)
{
    float deltaX = 0,
          deltaY = 0;

    if (IsKeyDown(KEY_W))
    {
        deltaX += player.dir.x * moveSpeed;
        deltaY += player.dir.y * moveSpeed;
    }
    else if (IsKeyDown(KEY_S))
    {
        deltaX -= player.dir.x * moveSpeed;
        deltaY -= player.dir.y * moveSpeed;
    }

    if (IsKeyDown(KEY_D))
    {
        deltaX -= player.dir.y * moveSpeed;
        deltaY += player.dir.x * moveSpeed;
    }
    else if (IsKeyDown(KEY_A))
    {
        deltaX += player.dir.y * moveSpeed;
        deltaY -= player.dir.x * moveSpeed;
    }

    float newX = player.pos.x + deltaX,
          newY = player.pos.y + deltaY;

    if (newX < (PLAYER_RADIUS + 1))
        newX = (PLAYER_RADIUS + 1);
    if (newX > (COLUMNS * TILE_SIZE) - (PLAYER_RADIUS + 1))
        newX = (COLUMNS * TILE_SIZE) - (PLAYER_RADIUS + 1);
    if (newY < (PLAYER_RADIUS + 1))
        newY = (PLAYER_RADIUS + 1);
    if (newY > (ROWS * TILE_SIZE) - (PLAYER_RADIUS + 1))
        newY = (ROWS * TILE_SIZE) - (PLAYER_RADIUS + 1);

    if (WORLD_MAP[(int)player.pos.y / TILE_SIZE][(int)(player.pos.x + sign(deltaX) * (PLAYER_RADIUS + 1)) / TILE_SIZE] == 0 &&
        WORLD_MAP[(int)player.pos.y / TILE_SIZE][(int)newX / TILE_SIZE] == 0)
        player.pos.x = newX;

    if (WORLD_MAP[(int)(player.pos.y + sign(deltaY) * (PLAYER_RADIUS + 1)) / TILE_SIZE][(int)player.pos.x / TILE_SIZE] == 0 &&
        WORLD_MAP[(int)newY / TILE_SIZE][(int)player.pos.x / TILE_SIZE] == 0)
        player.pos.y = newY;
}

void InitRotation(float rotSpeed)
{
    double oldDirX = player.dir.x;

    if (IsKeyDown(KEY_UP))
    {
        if (player.dir.x != 0)
        {
            float angle = (player.dir.x < 0 ? 1 : -1) * rotSpeed;
            player.dir.x = player.dir.x * cos(angle) - player.dir.y * sin(angle);
            player.dir.y = oldDirX * sin(angle) + player.dir.y * cos(angle);
        }
    }
    else if (IsKeyDown(KEY_DOWN))
    {
        if (player.dir.x != 0)
        {
            float angle = (player.dir.x > 0 ? 1 : -1) * rotSpeed;
            player.dir.x = player.dir.x * cos(angle) - player.dir.y * sin(angle);
            player.dir.y = oldDirX * sin(angle) + player.dir.y * cos(angle);
        }
    }
    else if (IsKeyDown(KEY_RIGHT))
    {
        player.dir.x = player.dir.x * cos(rotSpeed) - player.dir.y * sin(rotSpeed);
        player.dir.y = oldDirX * sin(rotSpeed) + player.dir.y * cos(rotSpeed);
    }
    else if (IsKeyDown(KEY_LEFT))
    {
        player.dir.x = player.dir.x * cos(-rotSpeed) - player.dir.y * sin(-rotSpeed);
        player.dir.y = oldDirX * sin(-rotSpeed) + player.dir.y * cos(-rotSpeed);
    }

    player.plane = (Vector2){-player.dir.y * FOV_SCALE, player.dir.x * FOV_SCALE};
}