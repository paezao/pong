#include "main_menu.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

void InitMainMenuScreen(int _screenWidth, int _screenHeight)
{
    screenHeight = _screenHeight;
    screenWidth = _screenWidth;
}

int UpdateMainMenuScreen()
{
    BeginDrawing();

    int ret = -1;

    ClearBackground(BLACK);

    Rectangle playButtonBounds = { 100, 100, 100, 40 };
    if(GuiButton(playButtonBounds, "PLAY"))
    {
        ret = 0;
    }

    Rectangle quitButtonBounds = { 100, 150, 100, 40 };
    if(GuiButton(quitButtonBounds, "QUIT"))
    {
        ret = 1;
    }

    EndDrawing();

    return ret;
}
