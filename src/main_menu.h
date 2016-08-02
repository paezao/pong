#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "raylib.h"

static int screenHeight, screenWidth;

static Sound menuSelectionSound;

void InitMainMenuScreen(int _screenWidth, int _screenHeight);
int UpdateMainMenuScreen();

#endif
