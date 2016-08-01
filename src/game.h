#ifndef GAME_H
#define GAME_H

#include "raylib.h"

enum GameState { GS_PLAYING = 0, GS_WON, GS_LOST, GS_MENU } currentGameState;

static struct Player
{
    Vector2 padPosition;
    Color padColor;
    int score;
} player1, player2;

static struct Ball
{
    Vector2 position;
    float radius;
    Vector2 speed;
    Color color;
} ball;

static int screenHeight, screenWidth, midScreenX, midScreenY;

static int padHeight = 50;
static int padWidth = 5;

static void InitPlayer(struct Player *player, const int posX, const int posY, Color color);
static void InitPlayers();
static void InitBall();
static void Draw();
static void Input();
static void Physics();

void InitGameScreen(int _screenWidth, int _screenHeight);
int UpdateGameScreen();

#endif
