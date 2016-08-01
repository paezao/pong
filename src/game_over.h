#ifndef GAME_OVER_H
#define GAME_OVER_H

#include "raylib.h"

static int screenHeight, screenWidth, midScreenX, midScreenY, returnValue, lost;

static void Draw();

void InitGameOverScreen(int _screenWidth, int _screenHeight, int _lost);
int UpdateGameOverScreen();

#endif
