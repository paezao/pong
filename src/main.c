#include "raylib.h"
#include "utils.h"
#include "main_menu.h"
#include "game.h"
#include "game_over.h"

static enum Screens { MAIN_MENU = 0, GAME, GAME_OVER, CREDITS } currentScreen;

static int shouldQuit = false;
static int screenWidth = 800;
static int screenHeight = 600;

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
    int gameState = UpdateGameScreen();
    int lost = 1;

    switch(gameState)
    {
        case GS_WON:
            lost = 0;
        case GS_LOST:
            currentScreen = GAME_OVER;
            InitGameOverScreen(screenWidth, screenHeight, lost);
            break;
        case GS_QUITTING:
            shouldQuit = true;
            break;
        case GS_QUITTING_TO_MENU:
            currentScreen = MAIN_MENU;
            InitMainMenuScreen(screenWidth, screenHeight);
            break;
        default:
            break;
    }
}

static void HandleGameOver()
{
    int ret = UpdateGameOverScreen();

    if(ret == 1)
    {
        currentScreen = GAME;
        InitGameScreen(screenWidth, screenHeight);
    }
    else if(ret == 2)
    {
        shouldQuit = true;
    }
    else if(ret == 3)
    {
        currentScreen = MAIN_MENU;
        InitMainMenuScreen(screenWidth, screenHeight);
    }
}

int main()
{

    //SetConfigFlags(FLAG_SHOW_LOGO);

    InitWindow(screenWidth, screenHeight, "Pong");

    InitAudioDevice();

    SetTargetFPS(144);

    currentScreen = MAIN_MENU;
    InitMainMenuScreen(screenWidth, screenHeight);

    while(!shouldQuit)
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
                HandleGameOver();
                break;
            case CREDITS:
                break;
        }
    }

    CloseAudioDevice();

    CloseWindow();

    return 0;
}

