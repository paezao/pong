#include "raylib.h"
#include "utils.h"

int main()
{
  int screenWidth = 800;
  int screenHeight = 600;

  int midScreenX = screenWidth / 2;
  int midScreenY = screenHeight / 2;

  int padHeight = 50;
  int padWidth = 5;
  float ballRadius = 5.0f;

  Vector2 ballPosition = { midScreenX, midScreenY };
  Vector2 ballSpeed = { -1.0f, 0.0f };

  int player1Position = midScreenY - padHeight / 2;
  int player2Position = midScreenY - padHeight / 2;

  int player1XPosition = 100;
  int player2XPosition = screenWidth - 100 - padWidth;

  int player1Score = 0;
  int player2Score = 0;

  InitWindow(screenWidth, screenHeight, "Pong");

  SetTargetFPS(144);

  while(!WindowShouldClose())
  {
    // Input
    if(IsKeyDown(KEY_W)) if(player1Position > 0) player1Position -= 1;
    if(IsKeyDown(KEY_S)) if(player1Position + padHeight < screenHeight) player1Position += 1;

    if(IsKeyDown(KEY_UP)) if(player2Position > 0) player2Position -= 1;
    if(IsKeyDown(KEY_DOWN)) if(player2Position + padHeight < screenHeight) player2Position += 1;

    // Check Scoring
    if(ballPosition.x < 0)
    {
      player2Score += 1;
      ballPosition.x = midScreenX;
      ballPosition.y = midScreenY;
      ballSpeed.x = -1.0f;
      ballSpeed.y = 0.0f;
    }
    else if(ballPosition.x > screenWidth)
    {
      player1Score += 1;
      ballPosition.x = midScreenX;
      ballPosition.y = midScreenY;
      ballSpeed.x = -1.0f;
      ballSpeed.y = 0.0f;
    }

    // Collisions
    Rectangle player1Rectangle = { player1XPosition, player1Position, padWidth, padHeight };
    if(CheckCollisionCircleRec(ballPosition, ballRadius, player1Rectangle))
    {
      ballSpeed.x *= -1;
      ballSpeed.y = GetRandomValue(-1, 1);
    }

    Rectangle player2Rectangle = { player2XPosition, player2Position, padWidth, padHeight };
    if(CheckCollisionCircleRec(ballPosition, ballRadius, player2Rectangle))
    {
      ballSpeed.x *= -1;
      ballSpeed.y = GetRandomValue(-1, 1);
    }
    
    // Ball Movement
    if(ballPosition.y > 0 && ballPosition.y < screenHeight)
    {
      ballPosition.x += ballSpeed.x;
      ballPosition.y += ballSpeed.y;
    }
    else
    {
      ballSpeed.y *= -1;
      ballPosition.x += ballSpeed.x;
      ballPosition.y += ballSpeed.y;
    }

    // Drawing
    BeginDrawing();

    ClearBackground(BLACK);

    // Divider
    DrawLine(midScreenX, 0, midScreenX, screenHeight, WHITE);

    // Draw Scores
    const char* player1ScoreText = FormatText("%i", player1Score);
    DrawText(player1ScoreText, midScreenX - 50 - MeasureText(player1ScoreText, 30), 20, 30, BLUE);
    DrawText(FormatText("%i", player2Score), midScreenX + 50, 20, 30, GREEN);

    // Player 1 Pad (Blue)
    DrawRectangle(player1XPosition, player1Position, padWidth, padHeight, BLUE); 

    // Player 2 Pad (Green)
    DrawRectangle(player2XPosition, player2Position, padWidth, padHeight, GREEN); 

    // Ball
    DrawCircle(ballPosition.x, ballPosition.y, ballRadius, RED);

    DrawFPS(10, 10);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
