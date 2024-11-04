#include <stdio.h>
#include "raylib.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void) {
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        for (int i = 0; i < 20; ++i) {
            DrawRectangle(0 + 30 * i, screenHeight - 20 * (i + 1), 30, 20 * (i + 1), (Color){50 + 10 * i, 50, 48, 255});
        }

        EndDrawing();
    }
    CloseWindow();
    return 0;
}