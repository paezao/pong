#include "raylib.h"
#include "utils.h"

int main()
{
  int screenWidth = 800;
  int screenHeight = 600;

  InitWindow(screenWidth, screenHeight, "Pong");

  SetTargetFPS(144);

  while(!WindowShouldClose())
  {
    BeginDrawing();

    ClearBackground(BLACK);

    DrawFPS(10, 10);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
