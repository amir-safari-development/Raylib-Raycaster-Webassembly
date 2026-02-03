#ifndef PLAYER_H
#define PLAYER_H

#include <math.h>
#include "map.h"
#include "raylib.h"

#define PLAYER_RADIUS 10
#define FOV_SCALE 0.66f

#define BASE_SPEED 200
#define BASE_ROT_SPEED 1.75f

typedef struct {
   Vector2 pos;
   Vector2 dir;
   Vector2 plane;
} Player;

extern Player player;

void PlacePlayer();
void DrawPlayer(int mode);
void InitMobility(float moveSpeed);
void InitRotation(float rotSpeed);
void CastRays(int x);

#endif