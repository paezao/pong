#include "game_over.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

void InitGameOverScreen(int _screenWidth, int _screenHeight, int _lost)
{
    screenWidth = _screenWidth;
    screenHeight = _screenHeight;
    midScreenX = screenWidth / 2;
    midScreenY = screenHeight / 2;
    lost = _lost;
    returnValue = 0;
}

int UpdateGameOverScreen()
{
    Draw();

    return returnValue;
}

static void Draw()
{
    BeginDrawing();

    ClearBackground(BLACK);

    const char *gameOverText = "You've won!";
    Color color = BLUE;

    if(lost == 1)
    {
        gameOverText = "You've lost!";
        color = RED;
    }

    DrawText(gameOverText, midScreenY + 100, midScreenY - MeasureText(gameOverText, 30) / 2, 30, color);

    Rectangle playButtonBounds = { 100, 100, 200, 40 };
    if(GuiButton(playButtonBounds, "PLAY AGAIN"))
    {
        returnValue = 1;
    }

    Rectangle quitToMenuButtonBounds = { 100, 150, 200, 40 };
    if(GuiButton(quitToMenuButtonBounds, "QUIT TO MAIN MENU"))
    {
        returnValue = 3;
    }

    Rectangle quitButtonBounds = { 100, 200, 200, 40 };
    if(GuiButton(quitButtonBounds, "QUIT TO DESKTOP"))
    {
        returnValue = 2;
    }

    EndDrawing();
}
