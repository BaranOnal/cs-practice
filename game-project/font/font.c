#include "raylib.h"


void DrawCenteredTextEx(Font font, const char* text, Vector2 position, float fontsize, float spacing, Color tint);

int main() {
    const int screenWidth = 960;
    const int screenHeight = 540;

    // Initialize window
    InitWindow(screenWidth, screenHeight, "baran");
    SetTargetFPS(60);

    Font baran = LoadFont("ayarlar/Winter Storm.ttf");

    Texture2D Backgorund = LoadTexture("ayarlar/sbackground.png");

        while (!WindowShouldClose()) {

          
        BeginDrawing();
        DrawTextureEx(Backgorund,(Vector2){0,0},0,1, WHITE);
        ClearBackground(RAYWHITE);

        // Draw text on the screen
        DrawCenteredTextEx(baran, "Start", (Vector2){ 480, 270 }, baran.baseSize, 0, BLACK);

        EndDrawing();
    }

    CloseWindow();
    UnloadFont(baran);
    UnloadTexture(Backgorund);
    return 0;
}

void DrawCenteredTextEx(Font font, const char* text, Vector2 position, float fontsize, float spacing, Color tint) {

    Vector2 text_dimension = MeasureTextEx(font, text, fontsize, spacing);

    Vector2 centered_pos;

    centered_pos.x = position.x - ((text_dimension.x) / 2);

    centered_pos.y = position.y - ((text_dimension.y) / 2);

    DrawTextEx(font, text, centered_pos, fontsize, spacing, tint);

}

/*
#include <raylib.h>

int main(void)
{
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "Texture Yükleme Örneği");

    Texture2D texture = LoadTexture("ayarlar/background.png");

    while (!WindowShouldClose())
    {
        BeginDrawing();

        DrawTexture(texture, 0,0, WHITE);

        EndDrawing();
    }

    UnloadTexture(texture);

    CloseWindow();

    return 0;
}
*/