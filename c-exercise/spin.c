#include <raylib.h>
#include <stdio.h>


//Sabitler
#define MAX_TUBES 120
#define FLOPPY_RADIUS 24
#define TUBES_WIDTH 80


// Fonksiyon prototipleri
Vector2 DrawCenteredTextEx(Font font, const char* text, Vector2 position, float fontSize, float spacing, Color tint);
Vector2 FindCornerForCenteredTextEx(Font font, const char* text, Vector2 position, float fontSize, float spacing);
Vector2 FindCornerForCenteredTextScaledEx(Font font, const char* text, Vector2 ratios, float fontSize, float spacing);
Vector2 DrawScaledCenteredTextEx(Font font, const char* text, Vector2 ratios, float fontSize, float spacing, Color tint);

void ExecuteMenu(int* p_start_button_state, int* p_options_button_state, int* p_exit_button_state);
void ExecuteOptions(int* p_options_button_state);
void ExecuteExit(int* p_exit_button_state);
static void ExecutePauseScreen(void);
static void ExecuteLoseScreen(void);

static void InitGame(void);         // Initialize
static void UpdateGame(void);       // One frame güccelleme
static void DrawGame(void);         // One frame çizme
static void UnloadGame(void);       // Unload game
static void UpdateDrawFrame(void);  // One frame çizimi
static void BirdRotation(int rotation);

// Yapý tanýmý
typedef struct {
    Font WinterTitleWindowed;
    Font WinterWindowed;
    Font WinterPopupWindowed;
    Font WinterDetailW;
} MyFont;


//Kuþun daire þeklinde hitboxsý için
typedef struct {
    Vector2 position;
    int radius;
    Color color;
} Floppy;

typedef struct {
    Rectangle rec;
    Color color;
    bool active;
} Tubes;

// Global deðiþkenler
static const int screenWidth = 960;
static const int screenHeight = 540;

static bool score_flag = false;
static bool gameOver = false;
static bool pause = false;
static bool exitWindow = false;



static int score = 0;
static int hiScore = 0;
static int rotation = -50;
static int musicOn = 1;
static Floppy bird = { 0 };
static Tubes tubes[(MAX_TUBES * 2) + 1] = { 0 };
static Vector2 tubesPos[MAX_TUBES] = { 0 };
static int tubesSpeedX = 0;
static int i = 0;

//Fontlar  görseller sound
MyFont MyWinter;
Texture2D Background;
Texture2D ReturnButton;
Texture2D PauseButton;
Texture2D PlayButton;
Texture2D Bird;
Sound LoseS;
Sound PointS;
Music GameMusic;


int framesCounter = 0;


int main() {

    InitWindow(screenWidth, screenHeight, "Bird");
    InitAudioDevice();
    InitGame();



    int options_button_state = 0;
    int start_button_state = 0;
    int exit_button_state = 0;
    int exit_button_state1 = 0;


    while (!WindowShouldClose() && !exitWindow) {

        BeginDrawing();
        UpdateMusicStream(GameMusic);
        PlayMusicStream(GameMusic);


        if (start_button_state) {

            UpdateDrawFrame();

        }
        else if (options_button_state) {
            ExecuteOptions(&options_button_state);

        }
        else if (exit_button_state)
        {
            ExecuteExit(&exit_button_state);
        }
        else if (!start_button_state && !options_button_state) {
            ExecuteMenu(&start_button_state, &options_button_state, &exit_button_state);

        }

        EndDrawing();
    }
    UnloadMusicStream(GameMusic);
    CloseAudioDevice();
    UnloadGame();

    return 0;
}

// Yardýmcý fonksiyonlar
Vector2 DrawCenteredTextEx(Font font, const char* text, Vector2 position, float fontSize, float spacing, Color tint) {
    Vector2 textsize = MeasureTextEx(font, text, fontSize, spacing);
    Vector2 centered_pos;

    centered_pos.x = position.x - (textsize.x / 2);
    centered_pos.y = position.y - (textsize.y / 2);

    DrawTextEx(font, text, centered_pos, fontSize, spacing, tint);

    return centered_pos;
}

Vector2 FindCornerForCenteredTextEx(Font font, const char* text, Vector2 position, float fontSize, float spacing) {
    Vector2 textsize = MeasureTextEx(font, text, fontSize, spacing);
    Vector2 centered_pos;

    centered_pos.x = position.x - (textsize.x / 2);
    centered_pos.y = position.y - (textsize.y / 2);

    return centered_pos;
}

void ExecuteMenu(int* p_start_button_state, int* p_options_button_state, int* p_exit_button_state) {
    DrawTextureEx(Background, (Vector2) { 0, 0 }, 0, 1, WHITE);

    DrawScaledCenteredTextEx(MyWinter.WinterTitleWindowed, "Flappy Bird", (Vector2) { 0.5, 1.0 / 3.0 }, 100, 0, RAYWHITE);

    Vector2 StartButtonCorner = FindCornerForCenteredTextScaledEx(MyWinter.WinterWindowed, "Start", (Vector2) { 0.5, 0.55 }, 50, 0);
    Rectangle Start;
    Start.x = StartButtonCorner.x;
    Start.y = StartButtonCorner.y;
    Start.width = MeasureTextEx(MyWinter.WinterWindowed, "Start", 1 * 50, 0).x;
    Start.height = MeasureTextEx(MyWinter.WinterWindowed, "Start", 1 * 50, 0).y;

    Vector2 OptionsButtonCorner = FindCornerForCenteredTextScaledEx(MyWinter.WinterWindowed, "Options", (Vector2) { 0.5, 0.65 }, 50, 0);
    Rectangle Options;
    Options.x = OptionsButtonCorner.x;
    Options.y = OptionsButtonCorner.y;
    Options.width = MeasureTextEx(MyWinter.WinterWindowed, "Options", 1 * 50, 0).x;
    Options.height = MeasureTextEx(MyWinter.WinterWindowed, "Options", 1 * 50, 0).y;

    Vector2 ExitButtonCorner = FindCornerForCenteredTextScaledEx(MyWinter.WinterWindowed, "Exit", (Vector2) { 0.5, 0.9 }, 50, 0);
    Rectangle Exit;
    Exit.x = ExitButtonCorner.x;
    Exit.y = ExitButtonCorner.y;
    Exit.width = MeasureTextEx(MyWinter.WinterWindowed, "Exit", 1 * 50, 0).x;
    Exit.height = MeasureTextEx(MyWinter.WinterWindowed, "Exit", 1 * 50, 0).y;



    if (CheckCollisionPointRec(GetMousePosition(), Start)) {
        DrawScaledCenteredTextEx(MyWinter.WinterPopupWindowed, "Start", (Vector2) { 0.5, 0.55 }, 55, 0, GREEN);

        if (IsMouseButtonPressed(0)) {
            *p_start_button_state = 1;
        }
    }
    else {
        DrawScaledCenteredTextEx(MyWinter.WinterWindowed, "Start", (Vector2) { 0.5, 0.55 }, 50, 0, RAYWHITE);
    }

    if (CheckCollisionPointRec(GetMousePosition(), Options)) {
        DrawScaledCenteredTextEx(MyWinter.WinterPopupWindowed, "Options", (Vector2) { 0.5, 0.65 }, 55, 0, GREEN);

        if (IsMouseButtonPressed(0)) {
            *p_options_button_state = 1;
        }
    }
    else {
        DrawScaledCenteredTextEx(MyWinter.WinterWindowed, "Options", (Vector2) { 0.5, 0.65 }, 50, 0, RAYWHITE);
    }

    if (CheckCollisionPointRec(GetMousePosition(), Exit)) {
        DrawScaledCenteredTextEx(MyWinter.WinterPopupWindowed, "Exit", (Vector2) { 0.5, 0.9 }, 55, 0, RED);

        if (IsMouseButtonPressed(0)) {

            *p_exit_button_state = 1;

        }
    }
    else {
        DrawScaledCenteredTextEx(MyWinter.WinterWindowed, "Exit", (Vector2) { 0.5, 0.9 }, 50, 0, RAYWHITE);
    }

}


void ExecuteOptions(int* p_options_button_state) {
    DrawTextureEx(Background, (Vector2) { 0, 0 }, 0, 1, WHITE);

    Vector2 MusicS = FindCornerForCenteredTextScaledEx(MyWinter.WinterWindowed, ("Music:ON"  "Music:OFF"), (Vector2) { 0.1, 0.18 }, 50, 0);
    Rectangle MusicR;
    MusicR.x = MusicS.x;
    MusicR.y = MusicS.y;
    MusicR.width = MeasureTextEx(MyWinter.WinterWindowed, ("Music:ON"  "Music:OFF"), 1 * 50, 0).x;
    MusicR.height = MeasureTextEx(MyWinter.WinterWindowed, ("Music:ON"  "Music:OFF"), 1 * 50, 0).y;

    DrawTextureEx(ReturnButton, (Vector2) { 10, 10 }, 0, 1, WHITE);

    Rectangle ReturnBounds = { 10, 10, ReturnButton.width , ReturnButton.height };
    if (CheckCollisionPointRec(GetMousePosition(), ReturnBounds) && IsMouseButtonPressed(0)) {
        *p_options_button_state = 0;
    }

    if (CheckCollisionPointRec(GetMousePosition(), MusicR) && IsMouseButtonPressed(0)) {
        if (musicOn) {
            DrawScaledCenteredTextEx(MyWinter.WinterWindowed, "Music:OFF", (Vector2) { 0.1, 0.18 }, 55, 0, RED);
            musicOn = 0; // Müzik kapatýldý
            SetMusicVolume(GameMusic, 0); // Müzik sesini 0 olarak ayarla
        }
        else {
            DrawScaledCenteredTextEx(MyWinter.WinterWindowed, "Music:ON", (Vector2) { 0.1, 0.18 }, 55, 0, GREEN);
            musicOn = 1; // Müzik açýldý
            SetMusicVolume(GameMusic, 1); // Müzik sesini 1 olarak ayarla
        }
    }

    if (musicOn) {
        DrawScaledCenteredTextEx(MyWinter.WinterWindowed, "Music:ON", (Vector2) { 0.1, 0.18 }, 50, 0, GREEN);
    }
    else {
        DrawScaledCenteredTextEx(MyWinter.WinterWindowed, "Music:OFF", (Vector2) { 0.1, 0.18 }, 50, 0, RED);
    }

}



void ExecuteExit(int* p_exit_button_state)
{
    DrawTextureEx(Background, (Vector2) { 0, 0 }, 0, 1, WHITE);

    Vector2 YesButton = FindCornerForCenteredTextScaledEx(MyWinter.WinterDetailW, "YES", (Vector2) { 0.45, 0.6 }, 32, 0, RED);
    Rectangle Exit1;
    Exit1.x = YesButton.x;
    Exit1.y = YesButton.y;
    Exit1.width = MeasureTextEx(MyWinter.WinterDetailW, "YES", 1 * 32, 0).x;
    Exit1.height = MeasureTextEx(MyWinter.WinterDetailW, "YES", 1 * 32, 0).y;

    Vector2 NoButton = FindCornerForCenteredTextScaledEx(MyWinter.WinterDetailW, "NO", (Vector2) { 0.55, 0.6 }, 32, 0, RED);
    Rectangle Return1;
    Return1.x = NoButton.x;
    Return1.y = NoButton.y;
    Return1.width = MeasureTextEx(MyWinter.WinterDetailW, "YES", 1 * 32, 0).x;
    Return1.height = MeasureTextEx(MyWinter.WinterDetailW, "YES", 1 * 32, 0).y;

    DrawScaledCenteredTextEx(MyWinter.WinterWindowed, "Are You Sure?", (Vector2) { 0.5, 0.5 }, 50, 0, WHITE);
    DrawScaledCenteredTextEx(MyWinter.WinterDetailW, "YES", (Vector2) { 0.45, 0.6 }, 32, 0, RED);
    DrawScaledCenteredTextEx(MyWinter.WinterDetailW, "NO", (Vector2) { 0.55, 0.6 }, 32, 0, GREEN);

    if (CheckCollisionPointRec(GetMousePosition(), Exit1) && IsMouseButtonPressed(0)) {
        exitWindow = true;
    }
    else if (CheckCollisionPointRec(GetMousePosition(), Return1) && IsMouseButtonPressed(0)) {

        *p_exit_button_state = 0;
    }
}


Vector2 DrawScaledCenteredTextEx(Font font, const char* text, Vector2 ratios, float fontSize, float spacing, Color tint) {
    return DrawCenteredTextEx(font, text, (Vector2) { ratios.x* GetScreenWidth(), ratios.y* GetScreenHeight() }, fontSize * 1, spacing, tint);
}


Vector2 FindCornerForCenteredTextScaledEx(Font font, const char* text, Vector2 ratios, float fontSize, float spacing) {

    return FindCornerForCenteredTextEx(font, text, (Vector2) { (ratios.x)* (float)GetScreenWidth(), (ratios.y)* (float)GetScreenHeight() }, fontSize * 1, spacing);
}

// Initialize game variables
void InitGame(void)
{
    SetTargetFPS(60);

    MyWinter.WinterTitleWindowed = LoadFontEx("options/Winter Storm.ttf", 100, NULL, 0);
    MyWinter.WinterWindowed = LoadFontEx("options/Winter Storm.ttf", 50, NULL, 0);
    MyWinter.WinterPopupWindowed = LoadFontEx("options/Winter Storm.ttf", 55, NULL, 0);
    MyWinter.WinterDetailW = LoadFontEx("options/Winter Storm.ttf", 32, NULL, 0);

    Background = LoadTexture("options/sbackground.png");
    ReturnButton = LoadTexture("options/returnicon.png");
    Bird = LoadTexture("options/bird1.png");
    PlayButton = LoadTexture("options/play_icon.png");
    PauseButton = LoadTexture("options/pause_icon.png");

    PointS = LoadSound("options/ping.mp3");
    LoseS = LoadSound("options/beeps.mp3");

    GameMusic = LoadMusicStream("options/Lost Woods.mp3");


    bird.radius = Bird.width / 2;
    bird.position = (Vector2){ 80, screenHeight / 2 - Bird.width };
    tubesSpeedX = 2;

    for (int i = 0; i < MAX_TUBES; i++)
    {
        tubesPos[i].x = 450 + 300 * i;
        tubesPos[i].y = -GetRandomValue(0, 350);
    }

    for (int i = 0; i < MAX_TUBES * 2; i += 2)
    {
        tubes[i].rec.x = tubesPos[i / 2].x;
        tubes[i].rec.y = tubesPos[i / 2].y;
        tubes[i].rec.width = TUBES_WIDTH;
        tubes[i].rec.height = 400;

        tubes[i + 1].rec.x = tubesPos[i / 2].x;
        tubes[i + 1].rec.y = 900 + tubesPos[i / 2].y - 350;
        tubes[i + 1].rec.width = TUBES_WIDTH;
        tubes[i + 1].rec.height = 350;

        tubes[i / 2].active = true;
    }

    score = 0;

    gameOver = false;
    score_flag = false;
    pause = false;


}


// Update game (one frame)
void UpdateGame(void)
{
    if (!gameOver)
    {

        rotation += 2;

        if (rotation >= 60)
        {
            rotation = 60;
        }

        framesCounter++;
        Rectangle PauseButtonBounds = { GetScreenWidth() - PauseButton.width - 10, 10, PauseButton.width , PauseButton.height }; // Ýkon sýnýrlarýný belirle

        if (IsKeyPressed('P') || (CheckCollisionPointRec(GetMousePosition(), PauseButtonBounds) && IsMouseButtonPressed(0))) pause = !pause;

        if (!pause)
        {
            for (int i = 0; i < MAX_TUBES; i++) tubesPos[i].x -= tubesSpeedX + (0.08 * i);

            for (int i = 0; i < MAX_TUBES * 2; i += 2)
            {
                tubes[i].rec.x = tubesPos[i / 2].x;
                tubes[i + 1].rec.x = tubesPos[i / 2].x;
            }


            if (IsKeyDown(KEY_SPACE) && !gameOver) {

                bird.position.y -= 5;
                rotation = -50;

            }
            else bird.position.y += 3;

            // Check Collisions
            for (int i = 0; i < MAX_TUBES * 2; i++)
            {

                // Kuþun alt sýnýr kontrolü ve game over durumu
                if (bird.position.y + bird.radius / 2 >= screenHeight) {
                    gameOver = true;
                    pause = false;
                }

                // Kuþun üst sýnýr kontrolü ve game over durumu
                if (bird.position.y - bird.radius / 2 <= 0) {
                    gameOver = true;
                    pause = false;
                }


                if (CheckCollisionCircleRec(bird.position, bird.radius, tubes[i].rec))
                {
                    gameOver = true;
                    pause = false;
                }
                else if ((tubesPos[i / 2].x < bird.position.x) && tubes[i / 2].active && !gameOver)//sonra bak koþullar yanlýþ
                {
                    score += 100;
                    tubes[i / 2].active = false;
                    score_flag = true;

                    if (score > hiScore) hiScore = score;

                }
            }
        }
    }
    else
    {
        if (IsKeyPressed(KEY_ENTER))
        {
            InitGame();
            gameOver = false;

        }
    }
}



// Draw game (one frame)
void DrawGame(void)
{
    ClearBackground(RAYWHITE);

    if (!gameOver)
    {
        DrawTextureEx(Background, (Vector2) { 0, 0 }, 0, 1, WHITE);
        //DrawTexture(Bird, bird.position.x - 24, bird.position.y - 24, WHITE);

        BirdRotation(rotation);



        // Draw tubes
        for (int i = 0; i <= MAX_TUBES; i++)
        {
            DrawRectangle(tubes[i * 2].rec.x, tubes[i * 2].rec.y, tubes[i * 2].rec.width, tubes[i * 2].rec.height, GRAY);
            DrawRectangle(tubes[i * 2 + 1].rec.x, tubes[i * 2 + 1].rec.y, tubes[i * 2 + 1].rec.width, tubes[i * 2 + 1].rec.height, GRAY);
        }

        // Anlýk olaylar
        if (score_flag)
        {
            PlaySound(PointS);
            score_flag = false;
        }
        PlaySound(LoseS);


        DrawScaledCenteredTextEx(MyWinter.WinterDetailW, TextFormat("%i", score), (Vector2) { 0.1, 0.1 }, 32, 0, BLACK);
        DrawScaledCenteredTextEx(MyWinter.WinterDetailW, TextFormat("HI-SCORE: %i", hiScore), (Vector2) { 0.1, 0.2 }, 32, 0, BLACK);
        DrawTextureEx(PauseButton, (Vector2) { GetScreenWidth() - (PlayButton.width + 10), 10 }, 0, 1, WHITE);


    }

    else if (gameOver)
        ExecuteLoseScreen();
    if (pause) ExecutePauseScreen();//con menüsü

}


// Unload game variables
void UnloadGame(void)
{

    UnloadFont(MyWinter.WinterTitleWindowed);
    UnloadFont(MyWinter.WinterWindowed);
    UnloadFont(MyWinter.WinterPopupWindowed);
    UnloadFont(MyWinter.WinterDetailW);

    UnloadTexture(Background);
    UnloadTexture(ReturnButton);
    UnloadTexture(Bird);
    UnloadTexture(PlayButton);
    UnloadTexture(PauseButton);

    UnloadSound(LoseS);
    UnloadSound(PointS);
    UnloadMusicStream(GameMusic);
    CloseWindow();

}

// Update and Draw (one frame)
void UpdateDrawFrame(void)
{
    UpdateGame();
    DrawGame();
}

void BirdRotation(int rotation)
{

    int frameWidth = Bird.width;
    int frameHeight = Bird.height;

    Rectangle sourceRec = { 0, 0, Bird.width, Bird.height };
    Rectangle destRec = { bird.position.x, bird.position.y , Bird.width, Bird.height };
    Vector2 origin = { Bird.width / 2, Bird.height / 2 };


    DrawTexturePro(Bird, sourceRec, destRec, origin, rotation, WHITE);


}

void ExecutePauseScreen(void)
{
    Vector2 Menutext = FindCornerForCenteredTextScaledEx(MyWinter.WinterWindowed, "MENU", (Vector2) { 0.5, 0.9 }, 32, 0);
    Rectangle MenuT;
    MenuT.x = Menutext.x;
    MenuT.y = Menutext.y;
    MenuT.width = MeasureTextEx(MyWinter.WinterWindowed, "Play Again", 1 * 50, 0).x;
    MenuT.height = MeasureTextEx(MyWinter.WinterWindowed, "Play Again", 1 * 50, 0).y;


    DrawTextureEx(Background, (Vector2) { 0, 0 }, 0, 1, WHITE);


    if ((framesCounter / 30) % 2)DrawScaledCenteredTextEx(MyWinter.WinterWindowed, "Paused", (Vector2) { 0.5, 0.5 }, 50, 0, WHITE);
    DrawScaledCenteredTextEx(MyWinter.WinterDetailW, TextFormat("SCORE:%i", score), (Vector2) { 0.5, 0.6 }, 32, 0, WHITE);
    DrawScaledCenteredTextEx(MyWinter.WinterDetailW, TextFormat("HI-SCORE: %i", hiScore), (Vector2) { 0.5, 0.7 }, 32, 0, WHITE);
    DrawTextureEx(PlayButton, (Vector2) { GetScreenWidth() - (PlayButton.width + 10), 10 }, 0, 1, WHITE);
    DrawScaledCenteredTextEx(MyWinter.WinterWindowed, "MENU", (Vector2) { 0.5, 0.9 }, 50, 0, WHITE);

    if (CheckCollisionPointRec(GetMousePosition(), MenuT) && IsMouseButtonPressed(0))
    {



    }
    //pause ekranýndan menüye dönmek yarým kaldý
}


void ExecuteLoseScreen(void)
{

    Vector2 AgainButtonCorner = FindCornerForCenteredTextScaledEx(MyWinter.WinterDetailW, "Play Again", (Vector2) { 0.5, 0.5 }, 32, 0);
    Rectangle AgainT;
    AgainT.x = AgainButtonCorner.x;
    AgainT.y = AgainButtonCorner.y;
    AgainT.width = MeasureTextEx(MyWinter.WinterWindowed, "Play Again", 1 * 50, 0).x;
    AgainT.height = MeasureTextEx(MyWinter.WinterWindowed, "Play Again", 1 * 50, 0).y;


    DrawTextureEx(Background, (Vector2) { 0, 0 }, 0, 1, WHITE);
    DrawScaledCenteredTextEx(MyWinter.WinterWindowed, "You Lost", (Vector2) { 0.5, 0.3 }, 50, 0, RED);
    //DrawScaledCenteredTextEx(MyWinter.WinterWindowed, "Play Again", (Vector2) { 0.5, 0.5 }, 50, 0, WHITE);

    if (CheckCollisionPointRec(GetMousePosition(), AgainT)) {
        DrawScaledCenteredTextEx(MyWinter.WinterPopupWindowed, "Play Again", (Vector2) { 0.5, 0.5 }, 55, 0, GREEN);
    }
    else {
        DrawScaledCenteredTextEx(MyWinter.WinterWindowed, "Play Again", (Vector2) { 0.5, 0.5 }, 50, 0, RAYWHITE);
    }


    DrawScaledCenteredTextEx(MyWinter.WinterDetailW, TextFormat("SCORE:%i", score), (Vector2) { 0.5, 0.7 }, 32, 0, WHITE);
    DrawScaledCenteredTextEx(MyWinter.WinterDetailW, TextFormat("HI-SCORE: %i", hiScore), (Vector2) { 0.5, 0.8 }, 32, 0, WHITE);

    if (CheckCollisionPointRec(GetMousePosition(), AgainT) && IsMouseButtonPressed(0)) {

        InitGame();
        gameOver = false;
    }
    DrawScaledCenteredTextEx(MyWinter.WinterWindowed, "MENU", (Vector2) { 0.5, 0.9 }, 50, 0, WHITE);

}