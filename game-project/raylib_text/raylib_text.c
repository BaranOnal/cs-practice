#include <raylib.h>

void DrawCenteredTextEx(Font font, const char* text, Vector2 position, float fontsize, float spacing, Color tint);

int main() {

	Texture2D troll;
	Sound beep;
	Music music;
	Font font;
	InitWindow(800, 450, "basic window");
	InitAudioDevice();
	//SetTargetFPS(144);

	troll = LoadTexture("source/trollface.png");
	beep = LoadSound("source/beeps.mp3");
	music = LoadMusicStream("source/heavenly.mp3");
	font = LoadFontEx("source/Euclid Regular.ttf",60,NULL,0);
		PlayMusicStream(music);

	float posX = -troll.width;

	while (!WindowShouldClose())
	{
		UpdateMusicStream(music);
		DrawCenteredTextEx(font, "Troll Face", (Vector2){ 400, 225 }, font.baseSize, 0, DARKGREEN);
	 
		posX += GetFrameTime() * 400;

		if (IsKeyPressed(KEY_SPACE))
		{
			StopMusicStream(music);
			PlayMusicStream(music);
		}
	

		if (posX > 800)
		{
			posX = -troll.width;
		}

		Rectangle trollRect;
		trollRect.x = 100;
		trollRect.y = 100;
		trollRect.width = troll.width;
		trollRect.height = troll.height;
		


		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			if (CheckCollisionPointRec(GetMousePosition(),trollRect))
			{
				PlaySound(beep);
			}
		}

		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawTexture(troll, 10, 10, WHITE);
		//DrawRectangle(posX, 0, 100, 100, BLUE);
		EndDrawing();
	}
	StopMusicStream(music);
	CloseAudioDevice();
	CloseWindow();

	return 0;
}

void DrawCenteredTextEx(Font font, const char* text, Vector2 position, float fontsize, float spacing, Color tint) 
{
	Vector2 text_dimension = MeasureTextEx(font, text, fontsize, spacing);

	Vector2 centered_pos;

	centered_pos.x = position.x - ((text_dimension.x) / 2);

	centered_pos.y = position.y - ((text_dimension.y) / 2);

	DrawTextEx(font, text, centered_pos, fontsize, spacing, tint);

}