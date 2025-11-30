/*******************************************************************************************
*
*   raylib [textures] example - Background scrolling
*
*   Example originally created with raylib 2.0, last time updated with raylib 2.5
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2019-2024 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 960;
    const int screenHeight = 540;

    InitWindow(screenWidth, screenHeight, "raylib [textures] example - background scrolling");

    // NOTE: Be careful, background width must be equal or bigger than screen width
    // if not, texture should be draw more than two times for scrolling effect
    Texture2D background = LoadTexture("aa/ground.png");
    Texture2D midground = LoadTexture("aa/sky.png");
    //Texture2D foreground = LoadTexture("resources/cyberpunk_street_foreground.png");

        float scrollingBack = 0.0f;
    float scrollingMid = 0.0f;
    float scrollingFore = 0.0f;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        scrollingBack -= 0.1f;
        scrollingMid -= 0.9f;
        //scrollingFore -= 1.0f;

        // NOTE: Texture is scaled twice its size, so it sould be considered on scrolling
        if (scrollingBack <= -background.width * 2) scrollingBack = 0;
        if (scrollingMid <= -midground.width * 2) scrollingMid = 0;
        //if (scrollingFore <= -foreground.width * 2) scrollingFore = 0;
        //----------------------------------------------------------------------------------

        // Draw
        
        BeginDrawing();

        ClearBackground(GetColor(0x052c46ff));

        int i = 1;
        // Draw background image twice
        // NOTE: Texture is scaled twice its size
            DrawTextureEx(background, (Vector2) { scrollingBack, 392 }, 0.0f, 1.0f, WHITE);
            DrawTextureEx(background, (Vector2) { background.width * i  + scrollingBack, 392 }, 0.0f, 1.0f, WHITE);
            DrawTextureEx(background, (Vector2) { background.width* (i + 1) + scrollingBack, 392 }, 0.0f, 1.0f, WHITE);

        // Draw midground image twice
        DrawTextureEx(midground, (Vector2) { scrollingMid, 0 }, 0.0f, 1.0f, WHITE);
        DrawTextureEx(midground, (Vector2) { midground.width * i  + scrollingMid, 0 }, 0.0f, 1.0f, WHITE);
        DrawTextureEx(midground, (Vector2) { midground.width * (i + 1) + scrollingMid, 0 }, 0.0f, 1.0f, WHITE);

        i++;
        // Draw foreground image twice
       // DrawTextureEx(foreground, (Vector2) { scrollingFore, 70 }, 0.0f, 2.0f, WHITE);
       // DrawTextureEx(foreground, (Vector2) { foreground.width * 2 + scrollingFore, 70 }, 0.0f, 2.0f, WHITE);

  

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(background);  // Unload background texture
    UnloadTexture(midground);   // Unload midground texture
   // UnloadTexture(foreground);  // Unload foreground texture

    CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
