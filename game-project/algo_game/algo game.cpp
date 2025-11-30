#include <stdio.h>

#include <raylib.h>


void DrawCenteredTextEx(Font font, const char* text, Vector2 position, float fontsize, float spacing, Color tint);

int main() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    // Initialize window
    InitWindow(screenWidth, screenHeight, "Baran");
    SetTargetFPS(60);

    Font baran = LoadFont("sources/Hello Florida Demo.otf");


    while (!WindowShouldClose()) {

        BeginDrawing();
        ClearBackground(WHITE);

        // Draw text on the screen
        DrawCenteredTextEx(baran, "Bunu euclidle yazdim!", { 400, 225 }, baran.baseSize, 0, BLACK);

        EndDrawing();
    }

    CloseWindow();
    UnloadFont(baran);

    return 0;
}

void DrawCenteredTextEx(Font font, const char* text, Vector2 position, float fontsize, float spacing, Color tint){

    Vector2 text_dimension = MeasureTextEx(font,text,fontsize,spacing);

    Vector2 centered_pos;
    
    centered_pos.x = position.x - ((text_dimension.x) / 2);

    centered_pos.y = position.y - ((text_dimension.y) / 2);

    DrawTextEx(font, text, centered_pos, fontsize, spacing, tint);

}
