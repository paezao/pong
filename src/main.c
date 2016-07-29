#include "raylib.h"
#include "utils.h"
#include "main_menu.h"
#include "game.h"

enum Screens { MAIN_MENU = 0, GAME, GAME_OVER, CREDITS } currentScreen;

int shouldQuit = false;

static void HandleMainMenu()
{
    int ret = UpdateMainMenuScreen();

    if(ret == 1)
    {
        shouldQuit = true;
    } 
    else if (ret == 0)
    {
        currentScreen = GAME;
        InitGameScreen(screenWidth, screenHeight);
    }
}

static void HandleGame()
{
    UpdateGameScreen();
}

int main()
{
    int screenWidth = 800;
    int screenHeight = 600;

    //SetConfigFlags(FLAG_SHOW_LOGO);

    InitWindow(screenWidth, screenHeight, "Pong");

    SetTargetFPS(144);

    currentScreen = MAIN_MENU;
    InitMainMenuScreen(screenWidth, screenHeight);

    while(!WindowShouldClose() && !shouldQuit)
    {
        switch(currentScreen)
        {
            case MAIN_MENU:
                HandleMainMenu();
                break;
            case GAME:
                HandleGame();
                break;
            case GAME_OVER:
                break;
            case CREDITS:
                break;
        }
    }

    CloseWindow();

    return 0;
}

