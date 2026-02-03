#include "raylib.h"
#include "map.h"
#include "player.h"
#include <stdio.h>

int main()
{
    ViewMode mode = STATE_2D;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Raycaster");
    SetTargetFPS(60);

    PlacePlayer();

    while (!WindowShouldClose())
    {
        float deltaTime = GetFrameTime();

        if (IsKeyPressed(KEY_M))
            mode = mode == STATE_2D ? STATE_3D : STATE_2D;

        InitMobility(BASE_SPEED * deltaTime);
        InitRotation(BASE_ROT_SPEED * deltaTime);

        BeginDrawing();

        if (mode == STATE_2D)
            InitEditMap();
        else
        {
            DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT / 2, LIGHTGRAY);
            DrawRectangle(0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2, WHITE);

            for (int x = 0; x <= SCREEN_WIDTH; x++)
                CastRays(x);
        }

        DrawMap(mode);
        DrawPlayer(mode);

        DrawText(TextFormat("FPS: %i", GetFPS()), 10, SCREEN_HEIGHT - 40, 20, RED);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}