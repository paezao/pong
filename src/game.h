#ifndef GAME_H
#define GAME_H

#include "raylib.h"

struct Player
{
    Vector2 padPosition;
    Color padColor;
    int score;
} player1, player2;

struct Ball
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
void UpdateGameScreen();

#endif
