/*******************************************************************************************
 * 
********************************************************************************************/
// TODO: ADD PROJECT DESCRIPTION
#include "raylib+.h"
#include "raymath.h"
#include <string.h>

//------------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------------

int main(void) {
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetExitKey(KEY_ESCAPE);

    SetTargetFPS(30);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Variable declarations
    //--------------------------------------------------------------------------------------

    // Player properties
    Vector2 size = {30, 50};
    Vector2 position = {(screenWidth-size.x)/2, (screenHeight-size.y)/2};

    // Player speed variables
    float baseSpeed = 2.0f;
    float runMult = 2.0f;
    float maxRunMult = 2.0f;
    float minRunMult = 2.0f;

    bool stealth = false;

    // Timers
    struct Timer textTimer = NewTimer(0.0f, 5.0f);
    // struct Timer textTimer2 = NewTimer(10.0f, 5.0f);
    
    char text[50] = "Press WASD or arrow keys to move!";

    // Textures
    // Texture2D playerIdle = LoadTexture("playerIdle.png");

    //--------------------------------------------------------------------------------------
    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // Changes the run multiplier
        if (IsKeyPressed(KEY_EQUAL)) runMult += (runMult == maxRunMult) ? 0.0f : 0.5f;
        if (IsKeyPressed(KEY_MINUS)) runMult -= (runMult == minRunMult) ? 0.0f : 0.5f; 

        // Changes player position
        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) position.x += baseSpeed * (IsKeyDown(KEY_LEFT_SHIFT) ? runMult : 1) / (IsKeyDown(KEY_LEFT_CONTROL) ? runMult : 1);
        if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) position.x -= baseSpeed * (IsKeyDown(KEY_LEFT_SHIFT) ? runMult : 1) / (IsKeyDown(KEY_LEFT_CONTROL) ? runMult : 1);
        if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) position.y -= baseSpeed * (IsKeyDown(KEY_LEFT_SHIFT) ? runMult : 1) / (IsKeyDown(KEY_LEFT_CONTROL) ? runMult : 1);
        if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) position.y += baseSpeed * (IsKeyDown(KEY_LEFT_SHIFT) ? runMult : 1) / (IsKeyDown(KEY_LEFT_CONTROL) ? runMult : 1);

        // Sets player position limits
        if (position.x < 0) position.x = 0;
        if (position.y + (stealth ? 15 : 0) < 0) position.y = (stealth ? -15 : 0);
        if (position.x + size.x > screenWidth) position.x = screenWidth - size.x;
        if (position.y + size.y > screenHeight) position.y = screenHeight - size.y;

        // Uncatagorized updates
        stealth = (IsKeyDown(KEY_LEFT_CONTROL) && !IsKeyDown(KEY_LEFT_SHIFT));
        strcpy(text, (UpdateTimer(&textTimer)) ? "Press shift to run and control to croutch!" : text);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText(text, (screenWidth-MeasureText(text, 20))/2, (screenHeight-20)/2, 20, LIGHTGRAY);

            DrawRectangleV(Vector2Add(position, (Vector2) {0, (stealth ? 15 : 0)}), Vector2Subtract(size, (Vector2) {0, (stealth ? 15 : 0)}), (stealth ? (Color) {0, 0, 0, 127} : (Color) {0, 0, 0, 255}));
            // DrawTextureV(playerIdle, position, (stealth ? (Color) {255, 255, 255, 127} : (Color) {255, 255, 255, 255}));

            DrawFPS(5, 5);
            DrawText(TextFormat("%.1f run multiplier", runMult), 5, 30, 20, LIME);
            DrawText(TextFormat("%.2f X-coord", position.x), 5, 55, 20, LIME);
            DrawText(TextFormat("%.2f Y-coord", position.y), 5, 80, 20, LIME);
            DrawText(TextFormat("%.2lf time", GetTime() - 1), 5, 105, 20, LIME);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
