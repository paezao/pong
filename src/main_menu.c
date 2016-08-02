#include "main_menu.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

void InitMainMenuScreen(int _screenWidth, int _screenHeight)
{
    screenHeight = _screenHeight;
    screenWidth = _screenWidth;

    menuSelectionSound = LoadSound("assets/sounds/selectSwitch152.wav");
}

int UpdateMainMenuScreen()
{
    BeginDrawing();

    int ret = -1;

    ClearBackground(BLACK);

    Rectangle playButtonBounds = { 100, 100, 100, 40 };
    if(GuiButton(playButtonBounds, "PLAY"))
    {
        PlaySound(menuSelectionSound);
        ret = 0;
    }

    Rectangle quitButtonBounds = { 100, 150, 100, 40 };
    if(GuiButton(quitButtonBounds, "QUIT"))
    {
        PlaySound(menuSelectionSound);
        ret = 1;
    }

    EndDrawing();

    return ret;
}
