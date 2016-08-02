#include "game.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

static void InitPlayer(struct Player *player, const int posX, const int posY, Color color)
{
    player->padPosition.x = posX;
    player->padPosition.y = posY;
    player->padColor = color;
    player->score = 0;
}

static void InitPlayers()
{
    InitPlayer(&player1, 100, midScreenY - padHeight / 2, BLUE);
    InitPlayer(&player2, screenWidth - 100 - padWidth, midScreenY - padHeight / 2, GREEN);
}

static void InitBall()
{
    ball.position.x = midScreenX;
    ball.position.y = midScreenY;
    ball.radius = 5.0f;
    ball.speed.x = -1;
    ball.color = RED;
}

void InitGameScreen(int _screenWidth, int _screenHeight)
{
    screenWidth = _screenWidth;
    screenHeight = _screenHeight;
    midScreenX = screenWidth / 2;
    midScreenY = screenHeight / 2;

    menuSelectionSound = LoadSound("assets/sounds/selectSwitch152.wav");
    padHitSound = LoadSound("assets/sounds/hitDamage053.wav");
    scoreSound = LoadSound("assets/sounds/powerUp018.wav");

    currentGameState = GS_PLAYING;

    InitPlayers();
    InitBall();
}

int UpdateGameScreen()
{
    if(currentGameState == GS_PLAYING)
    {
        Physics();
        Input();
        Draw();
    }
    else
    {
        DrawMenu();
    }

    return currentGameState;
}

static void Draw()
{
    BeginDrawing();

    ClearBackground(BLACK);

    // Divider
    DrawLine(midScreenX, 0, midScreenX, screenHeight, WHITE);

    // Draw Scores
    const char* player1ScoreText = FormatText("%i", player1.score);
    DrawText(player1ScoreText, midScreenX - 50 - MeasureText(player1ScoreText, 30), 20, 30, BLUE);
    DrawText(FormatText("%i", player2.score), midScreenX + 50, 20, 30, GREEN);

    // Player 1 Pad (Blue)
    DrawRectangle(player1.padPosition.x, player1.padPosition.y, padWidth, padHeight, player1.padColor); 

    // Player 2 Pad (Green)
    DrawRectangle(player2.padPosition.x, player2.padPosition.y, padWidth, padHeight, player2.padColor); 

    // Ball
    DrawCircle(ball.position.x, ball.position.y, ball.radius, ball.color);
    
    DrawFPS(10, 10);

    EndDrawing();
}

static void Input()
{
    if(IsKeyDown(KEY_W)) if(player1.padPosition.y > 0) player1.padPosition.y -= 1;
    if(IsKeyDown(KEY_S)) if(player1.padPosition.y + padHeight < screenHeight) player1.padPosition.y += 1;

    if(IsKeyDown(KEY_UP)) if(player2.padPosition.y > 0) player2.padPosition.y -= 1;
    if(IsKeyDown(KEY_DOWN)) if(player2.padPosition.y + padHeight < screenHeight) player2.padPosition.y += 1;

    if(IsKeyDown(KEY_ESCAPE))
    {
        currentGameState = GS_MENU;
    }
}

static void Physics()
{
    if(ball.position.x < 0)
    {
        PlaySound(scoreSound);
        player2.score += 1;
        ball.position.x = midScreenX;
        ball.position.y = midScreenY;
        ball.speed.x = -1.0f;
        ball.speed.y = 0.0f;
    }
    else if(ball.position.x > screenWidth)
    {
        PlaySound(scoreSound);
        player1.score += 1;
        ball.position.x = midScreenX;
        ball.position.y = midScreenY;
        ball.speed.x = -1.0f;
        ball.speed.y = 0.0f;
    }

    if(player1.score >= 2)
    {
        currentGameState = GS_WON;
    }
    else if(player2.score >= 2)
    {
        currentGameState = GS_LOST;
    }

    // Collisions
    Rectangle player1Rectangle = { player1.padPosition.x, player1.padPosition.y, padWidth, padHeight };
    if(CheckCollisionCircleRec(ball.position, ball.radius, player1Rectangle))
    {
        PlaySound(padHitSound);
        ball.speed.x *= -1;
        ball.speed.y = GetRandomValue(-1, 1);
    }

    Rectangle player2Rectangle = { player2.padPosition.x, player2.padPosition.y, padWidth, padHeight };
    if(CheckCollisionCircleRec(ball.position, ball.radius, player2Rectangle))
    {
        PlaySound(padHitSound);
        ball.speed.x *= -1;
        ball.speed.y = GetRandomValue(-1, 1);
    }

    // Ball Movement
    if(ball.position.y > 0 && ball.position.y < screenHeight)
    {
        ball.position.x += ball.speed.x;
        ball.position.y += ball.speed.y;
    }
    else
    {
        ball.speed.y *= -1;
        ball.position.x += ball.speed.x;
        ball.position.y += ball.speed.y;
    }
}

static void DrawMenu()
{
    BeginDrawing();

    Rectangle playButtonBounds = { 100, 100, 150, 40 };
    if(GuiButton(playButtonBounds, "CONTINUE"))
    {
        currentGameState = GS_PLAYING;
        PlaySound(menuSelectionSound);
    }

    Rectangle quitToMenuButtonBounds = { 100, 150, 150, 40 };
    if(GuiButton(quitToMenuButtonBounds, "QUIT TO MENU"))
    {
        currentGameState = GS_QUITTING_TO_MENU;
        PlaySound(menuSelectionSound);
    }

    Rectangle quitButtonBounds = { 100, 200, 150, 40 };
    if(GuiButton(quitButtonBounds, "QUIT TO DESKTOP"))
    {
        currentGameState = GS_QUITTING;
    }

    EndDrawing();
}
