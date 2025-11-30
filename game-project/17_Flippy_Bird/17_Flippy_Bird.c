#include <raylib.h>
#include <stdio.h>


//Sabitler
#define MAX_TUBES 120
#define FLOPPY_RADIUS 24
#define TUBES_WIDTH 80


// Fonksiyon prototipleri
Vector2 RenderCenteredText(Font font, const char* text, Vector2 position, float fontSize, float spacing, Color tint);
Vector2 CalculateCenteredTextCorner(Font font, const char* text, Vector2 position, float fontSize, float spacing);
Vector2 GetScaledCenteredTextCorner(Font font, const char* text, Vector2 ratios, float fontSize, float spacing);
Vector2 DrawScaledCenteredText(Font font, const char* text, Vector2 ratios, float fontSize, float spacing, Color tint);

void ExecuteMenu(int* p_start_button_state, int* p_options_button_state, int* p_exit_button_state, int* p_inventory_button_state);
void ExecuteOptions(int* p_options_button_state);
void ExecuteExit(int* p_exit_button_state);
void ExecuteTheme(int* p_Theme_button_state);
void ExecutePauseScreen(void);
void ExecuteLoseScreen(void);
void DrawBackgroundTexture(int drawbackground);
void SelectBirdTexture(int selectbird);
void SelectBlockTexture(int selectblok);
void ScrollingBackground(void);
void BirdRotation(Texture2D texture, int rotation);
void ReverseMode(void);

void InitGame(void);         // Initialize
void UpdateGame(void);       // One frame g¸ccelleme
void DrawGame(void);         // One frame Áizme
void UnloadGame(void);       // Unload game
void UpdateDrawFrame(void);  // One frame Áizimi




// Yapı tanımları
typedef struct {
    Font WinterTitleWindowed;
    Font WinterWindowed;
    Font WinterPopupWindowed;
    Font WinterDetailW;
} MyFont;


//Hitbox daire 
typedef struct {
    Vector2 position;
    int radius;
} Floppy;

typedef struct {
    Rectangle rec;
    Color color;
    bool active;
} Tubes;

// Global değişkenler
static const int screenWidth = 960;
static const int screenHeight = 540;


bool score_flag = false;
bool gameOver = false;
bool pause = false;
bool exitWindow = false;
bool modbutton = false;


int score = 0;
int hiScore = 0;

int rotation = 0;

float scrollingBack = 0.0f;
float scrollingFore = 0.0f;

int musicOn = 1;
int soundOn = 1;
int modOn = 1;

int tubesSpeedX = 0;//tüplerin hızları

int framesCounter = 0;
int modeCounter;
int reverse_icon = 0;

int options_button_state = 0;
int start_button_state = 0;
int exit_button_state = 0;
int exit_button_state1 = 0;
int topten_button_state = 0;
int theme_button_state = 0;


bool drawbackground = false;
bool selectbird = false;
bool selectblok = false;

int background_texture = 1;
int bird_texture = 1;
int block_texture = 1;



Floppy bird = { 0 };

Tubes tubes[(MAX_TUBES * 2) + 1] = { 0 };
Vector2 tubesPos[MAX_TUBES] = { 0 };




//Fontlar,görsel,ses
MyFont MyWinter;


Texture2D ReturnButton;
Texture2D PauseButton;
Texture2D PlayButton;
Texture2D ReverseIcon;


Sound LoseS;
Sound PointS;

Music GameMusic;

Texture2D Bird;
Texture2D Astronaut;
Texture2D Ghost;
Texture2D Finn;

Texture2D Classic;
Texture2D background;
Texture2D background2;
Texture2D foreground;

Texture2D City;
Texture2D City2;
Texture2D Space;
Texture2D Desert;
Texture2D Gray;

Texture2D texture;

Texture2D Apartment;
Texture2D Apartment2;//upside down
Texture2D SpaceShip;
Texture2D SpaceShip2;//upside down
Texture2D GrayBlock;

Texture2D Temp1;
Texture2D Temp2;
Texture2D background_temp;




int main() {

    InitWindow(screenWidth, screenHeight, "Flippy Bird");
    InitAudioDevice();
    InitGame();


    while (!WindowShouldClose() && !exitWindow) {

        BeginDrawing();
        UpdateMusicStream(GameMusic);
        if (musicOn)
        {
            PlayMusicStream(GameMusic);
        }
        else
        {
            StopMusicStream(GameMusic);
        }
        if (!soundOn)
        {
            StopSound(LoseS);
            StopSound(PointS);
        }
        if (start_button_state) {

            UpdateDrawFrame();

        }
        else if (options_button_state) {
            ExecuteOptions(&options_button_state);

        }
        else if (theme_button_state) {

            ExecuteTheme(&theme_button_state);

        }
        else if (drawbackground)
        {
            DrawBackgroundTexture(drawbackground);
        }
        else if (selectbird)
        {
            SelectBirdTexture(selectbird);
        }
        else if (selectblok)
        {
            SelectBlockTexture(selectblok);
        }
        else if (options_button_state) {
            ExecuteOptions(&options_button_state);

        }
        else if (exit_button_state)
        {
            ExecuteExit(&exit_button_state);
        }
        else if (!start_button_state && !options_button_state) {
            ExecuteMenu(&start_button_state, &options_button_state, &exit_button_state, &theme_button_state);

        }

        EndDrawing();
    }
    UnloadMusicStream(GameMusic);
    CloseAudioDevice();
    UnloadGame();

    return 0;
}

// Yard˝mc˝ fonksiyonlar
Vector2 RenderCenteredText(Font font, const char* text, Vector2 position, float fontSize, float spacing, Color tint) {
    Vector2 textsize = MeasureTextEx(font, text, fontSize, spacing);
    Vector2 centered_pos;

    centered_pos.x = position.x - (textsize.x / 2);
    centered_pos.y = position.y - (textsize.y / 2);

    DrawTextEx(font, text, centered_pos, fontSize, spacing, tint);

    return centered_pos;
}


Vector2 CalculateCenteredTextCorner(Font font, const char* text, Vector2 position, float fontSize, float spacing) {
    Vector2 textsize = MeasureTextEx(font, text, fontSize, spacing);
    Vector2 centered_pos;

    centered_pos.x = position.x - (textsize.x / 2);
    centered_pos.y = position.y - (textsize.y / 2);

    return centered_pos;
}


Vector2 GetScaledCenteredTextCorner(Font font, const char* text, Vector2 ratios, float fontSize, float spacing) {

    return CalculateCenteredTextCorner(font, text, (Vector2) { (ratios.x)* (float)GetScreenWidth(), (ratios.y)* (float)GetScreenHeight() }, fontSize * 1, spacing);
}


Vector2 DrawScaledCenteredText(Font font, const char* text, Vector2 ratios, float fontSize, float spacing, Color tint) {
    return RenderCenteredText(font, text, (Vector2) { ratios.x* GetScreenWidth(), ratios.y* GetScreenHeight() }, fontSize * 1, spacing, tint);
}


void ExecuteMenu(int* p_start_button_state, int* p_options_button_state, int* p_exit_button_state, int* p_inventory_button_state) {

    DrawBackgroundTexture(drawbackground);
    PauseSound(LoseS);

    DrawScaledCenteredText(MyWinter.WinterTitleWindowed, "Flippy Bird", (Vector2) { 0.5, 0.3 }, 100, 0, RAYWHITE);

    Vector2 StartButtonCorner = GetScaledCenteredTextCorner(MyWinter.WinterWindowed, "Start", (Vector2) { 0.5, 0.45 }, 50, 0);
    Rectangle Start;
    Start.x = StartButtonCorner.x;
    Start.y = StartButtonCorner.y;
    Start.width = MeasureTextEx(MyWinter.WinterWindowed, "Start", 50, 0).x;
    Start.height = MeasureTextEx(MyWinter.WinterWindowed, "Start", 50, 0).y;

    Vector2 OptionsButtonCorner = GetScaledCenteredTextCorner(MyWinter.WinterWindowed, "Options", (Vector2) { 0.5, 0.55 }, 50, 0);
    Rectangle Options;
    Options.x = OptionsButtonCorner.x;
    Options.y = OptionsButtonCorner.y;
    Options.width = MeasureTextEx(MyWinter.WinterWindowed, "Options", 50, 0).x;
    Options.height = MeasureTextEx(MyWinter.WinterWindowed, "Options", 50, 0).y;

    Vector2 ExitButtonCorner = GetScaledCenteredTextCorner(MyWinter.WinterWindowed, "Exit", (Vector2) { 0.5, 0.9 }, 50, 0);
    Rectangle Exit;
    Exit.x = ExitButtonCorner.x;
    Exit.y = ExitButtonCorner.y;
    Exit.width = MeasureTextEx(MyWinter.WinterWindowed, "Exit", 50, 0).x;
    Exit.height = MeasureTextEx(MyWinter.WinterWindowed, "Exit", 50, 0).y;

    Vector2 ThemeButtonCorner = GetScaledCenteredTextCorner(MyWinter.WinterWindowed, "Theme", (Vector2) { 0.5, 0.65 }, 50, 0);
    Rectangle Theme;
    Theme.x = ThemeButtonCorner.x;
    Theme.y = ThemeButtonCorner.y;
    Theme.width = MeasureTextEx(MyWinter.WinterWindowed, "Theme", 50, 0).x;
    Theme.height = MeasureTextEx(MyWinter.WinterWindowed, "Theme", 50, 0).y;


    if (CheckCollisionPointRec(GetMousePosition(), Start)) {
        DrawScaledCenteredText(MyWinter.WinterPopupWindowed, "Start", (Vector2) { 0.5, 0.45 }, 55, 0, GREEN);

        if (IsMouseButtonPressed(0)) {
            *p_start_button_state = 1;
        }
    }
    else {
        DrawScaledCenteredText(MyWinter.WinterWindowed, "Start", (Vector2) { 0.5, 0.45 }, 50, 0, RAYWHITE);
    }

    if (CheckCollisionPointRec(GetMousePosition(), Options)) {
        DrawScaledCenteredText(MyWinter.WinterPopupWindowed, "Options", (Vector2) { 0.5, 0.55 }, 55, 0, GREEN);

        if (IsMouseButtonPressed(0)) {
            *p_options_button_state = 1;
        }
    }
    else {
        DrawScaledCenteredText(MyWinter.WinterWindowed, "Options", (Vector2) { 0.5, 0.55 }, 50, 0, RAYWHITE);
    }
    if (CheckCollisionPointRec(GetMousePosition(), Theme)) {
        DrawScaledCenteredText(MyWinter.WinterPopupWindowed, "Theme", (Vector2) { 0.5, 0.65 }, 55, 0, GREEN);

        if (IsMouseButtonPressed(0)) {
            *p_inventory_button_state = 1;

        }
    }
    else {
        DrawScaledCenteredText(MyWinter.WinterWindowed, "Theme", (Vector2) { 0.5, 0.65 }, 50, 0, RAYWHITE);
    }


    if (CheckCollisionPointRec(GetMousePosition(), Exit)) {
        DrawScaledCenteredText(MyWinter.WinterPopupWindowed, "Exit", (Vector2) { 0.5, 0.9 }, 55, 0, RED);

        if (IsMouseButtonPressed(0)) {

            *p_exit_button_state = 1;

        }
    }
    else {
        DrawScaledCenteredText(MyWinter.WinterWindowed, "Exit", (Vector2) { 0.5, 0.9 }, 50, 0, RAYWHITE);
    }

}


void ExecuteOptions(int* p_options_button_state) {
    DrawBackgroundTexture(drawbackground);

    Rectangle ReturnBounds = { 10, 10, ReturnButton.width , ReturnButton.height };
    if (CheckCollisionPointRec(GetMousePosition(), ReturnBounds) && IsMouseButtonPressed(0)) {
        *p_options_button_state = 0;
    }

    Vector2 MusicS = GetScaledCenteredTextCorner(MyWinter.WinterWindowed, ("Music:ON"  "Music:OFF"), (Vector2) { 0.1, 0.18 }, 50, 0);
    Rectangle MusicR;
    MusicR.x = MusicS.x;
    MusicR.y = MusicS.y;
    MusicR.width = MeasureTextEx(MyWinter.WinterWindowed, ("Music:ON"  "Music:OFF"), 50, 0).x;
    MusicR.height = MeasureTextEx(MyWinter.WinterWindowed, ("Music:ON"  "Music:OFF"), 50, 0).y;

    Vector2 SoundS = GetScaledCenteredTextCorner(MyWinter.WinterWindowed, ("Sound:ON"  "Sound:OFF"), (Vector2) { 0.1, 0.28 }, 50, 0);
    Rectangle SoundR;
    SoundR.x = SoundS.x;
    SoundR.y = SoundS.y;
    SoundR.width = MeasureTextEx(MyWinter.WinterWindowed, ("Sound:ON"  "Sound:OFF"), 50, 0).x;
    SoundR.height = MeasureTextEx(MyWinter.WinterWindowed, ("Sound:ON"  "Sound:OFF"), 50, 0).y;

    Vector2 ModButton = GetScaledCenteredTextCorner(MyWinter.WinterWindowed, ("Reverse Mode:ON"  "Reverse Mode:OFF"), (Vector2) { 0.17, 0.38 }, 50, 0);
    Rectangle ModR;
    ModR.x = ModButton.x;
    ModR.y = ModButton.y;
    ModR.width = MeasureTextEx(MyWinter.WinterWindowed, ("Reverse Mode:ON"  "Reverse Mode:OFF"), 50, 0).x;
    ModR.height = MeasureTextEx(MyWinter.WinterWindowed, ("Reverse Mode:ON"  "Reverse Mode:OFF"), 50, 0).y;

    DrawTextureEx(ReturnButton, (Vector2) { 10, 10 }, 0, 1, WHITE);

    if (CheckCollisionPointRec(GetMousePosition(), ModR) && IsMouseButtonPressed(0)) {
        if (modOn) {
            DrawScaledCenteredText(MyWinter.WinterWindowed, "Reverse Mode:OFF", (Vector2) { 0.17, 0.38 }, 55, 0, RED);
            modOn = 0;
        }
        else {
            DrawScaledCenteredText(MyWinter.WinterWindowed, "Reverse Mode:ON", (Vector2) { 0.17, 0.38 }, 55, 0, GREEN);
            modOn = 1;
        }
    }

    if (modOn) {
        DrawScaledCenteredText(MyWinter.WinterWindowed, "Reverse Mode:ON", (Vector2) { 0.17, 0.38 }, 50, 0, GREEN);
    }
    else {
        DrawScaledCenteredText(MyWinter.WinterWindowed, "Reverse Mode:OFF", (Vector2) { 0.17, 0.38 }, 50, 0, RED);
    }



    if (CheckCollisionPointRec(GetMousePosition(), MusicR) && IsMouseButtonPressed(0)) {
        if (musicOn)
        {
            DrawScaledCenteredText(MyWinter.WinterWindowed, "Music:OFF", (Vector2) { 0.1, 0.18 }, 55, 0, RED);
            musicOn = 0; // Müzik kapatıldı

        }
        else
        {
            DrawScaledCenteredText(MyWinter.WinterWindowed, "Music:ON", (Vector2) { 0.1, 0.18 }, 55, 0, GREEN);
            musicOn = 1; // Müzik açıldı
        }
    }

    if (musicOn) {
        DrawScaledCenteredText(MyWinter.WinterWindowed, "Music:ON", (Vector2) { 0.1, 0.18 }, 50, 0, GREEN);
    }
    else {
        DrawScaledCenteredText(MyWinter.WinterWindowed, "Music:OFF", (Vector2) { 0.1, 0.18 }, 50, 0, RED);
    }


    if (CheckCollisionPointRec(GetMousePosition(), SoundR) && IsMouseButtonPressed(0))
    {
        if (soundOn)
        {
            DrawScaledCenteredText(MyWinter.WinterWindowed, "Sound:OFF", (Vector2) { 0.1, 0.28 }, 55, 0, RED);
            soundOn = 0; //Sound açma kapama 


        }
        else
        {
            DrawScaledCenteredText(MyWinter.WinterWindowed, "Sound:ON", (Vector2) { 0.1, 0.28 }, 55, 0, GREEN);
            soundOn = 1; 


        }
    }

    if (soundOn) {
        DrawScaledCenteredText(MyWinter.WinterWindowed, "Sound:ON", (Vector2) { 0.1, 0.28 }, 50, 0, GREEN);
    }
    else {
        DrawScaledCenteredText(MyWinter.WinterWindowed, "Sound:OFF", (Vector2) { 0.1, 0.28 }, 50, 0, RED);
    }

}


void ExecuteExit(int* p_exit_button_state)
{
    DrawBackgroundTexture(drawbackground);

    Vector2 YesButton = GetScaledCenteredTextCorner(MyWinter.WinterDetailW, "YES", (Vector2) { 0.45, 0.6 }, 32, 0);
    Rectangle Exit1;
    Exit1.x = YesButton.x;
    Exit1.y = YesButton.y;
    Exit1.width = MeasureTextEx(MyWinter.WinterDetailW, "YES", 32, 0).x;
    Exit1.height = MeasureTextEx(MyWinter.WinterDetailW, "YES", 32, 0).y;

    Vector2 NoButton = GetScaledCenteredTextCorner(MyWinter.WinterDetailW, "NO", (Vector2) { 0.55, 0.6 }, 32, 0);
    Rectangle Return1;
    Return1.x = NoButton.x;
    Return1.y = NoButton.y;
    Return1.width = MeasureTextEx(MyWinter.WinterDetailW, "YES", 32, 0).x;
    Return1.height = MeasureTextEx(MyWinter.WinterDetailW, "YES", 32, 0).y;

    DrawScaledCenteredText(MyWinter.WinterWindowed, "Are You Sure?", (Vector2) { 0.5, 0.5 }, 50, 0, WHITE);
    DrawScaledCenteredText(MyWinter.WinterDetailW, "YES", (Vector2) { 0.45, 0.6 }, 32, 0, RED);
    DrawScaledCenteredText(MyWinter.WinterDetailW, "NO", (Vector2) { 0.55, 0.6 }, 32, 0, GREEN);

    if (CheckCollisionPointRec(GetMousePosition(), Exit1) && IsMouseButtonPressed(0)) {
        exitWindow = true;
    }
    else if (CheckCollisionPointRec(GetMousePosition(), Return1) && IsMouseButtonPressed(0)) {

        *p_exit_button_state = 0;
    }
}



void ExecuteTheme(int* p_theme_button_state)
{

    DrawTexture(Gray, 0, 0, GRAY);
    DrawTextureEx(ReturnButton, (Vector2) { 10, 10 }, 0, 1, WHITE);

    Rectangle ReturnBounds = { 10, 10, ReturnButton.width , ReturnButton.height };
    if (CheckCollisionPointRec(GetMousePosition(), ReturnBounds) && IsMouseButtonPressed(0)) {
        *p_theme_button_state = 0;
        drawbackground = 0;
        selectbird = 0;
        selectblok = 0;
    }

    Vector2 MapButton = GetScaledCenteredTextCorner(MyWinter.WinterWindowed, "MAPS", (Vector2) { 0.3, 0.5 }, 50, 0);
    Rectangle MapTextures;
    MapTextures.x = MapButton.x;
    MapTextures.y = MapButton.y;
    MapTextures.width = MeasureTextEx(MyWinter.WinterWindowed, "MAPS", 50, 0).x;
    MapTextures.height = MeasureTextEx(MyWinter.WinterWindowed, "MAPS", 50, 0).y;

    Vector2 BirdButton = GetScaledCenteredTextCorner(MyWinter.WinterWindowed, "BIRDS", (Vector2) { 0.5, 0.5 }, 32, 0);
    Rectangle BirdTextures;
    BirdTextures.x = BirdButton.x;
    BirdTextures.y = BirdButton.y;
    BirdTextures.width = MeasureTextEx(MyWinter.WinterWindowed, "BIRDS", 50, 0).x;
    BirdTextures.height = MeasureTextEx(MyWinter.WinterWindowed, "BIRDS", 50, 0).y;

    Vector2 BlockButton = GetScaledCenteredTextCorner(MyWinter.WinterWindowed, "BLOCKS", (Vector2) { 0.7, 0.5 }, 32, 0);
    Rectangle BlockTextures;
    BlockTextures.x = BlockButton.x;
    BlockTextures.y = BlockButton.y;
    BlockTextures.width = MeasureTextEx(MyWinter.WinterWindowed, "BLOCKS", 50, 0).x;
    BlockTextures.height = MeasureTextEx(MyWinter.WinterWindowed, "BLOCKS", 50, 0).y;


    if (CheckCollisionPointRec(GetMousePosition(), MapTextures)) {
        DrawScaledCenteredText(MyWinter.WinterPopupWindowed, "MAPS", (Vector2) { 0.3, 0.5 }, 55, 0, GREEN);

        if (IsMouseButtonPressed(0)) {
            *p_theme_button_state = 0;
            selectbird = 0;
            selectblok = 0;
            drawbackground = 1;
        }
    }
    else {
        DrawScaledCenteredText(MyWinter.WinterWindowed, "MAPS", (Vector2) { 0.3, 0.5 }, 50, 0, RAYWHITE);
    }

    if (CheckCollisionPointRec(GetMousePosition(), BirdTextures)) {
        DrawScaledCenteredText(MyWinter.WinterPopupWindowed, "BIRDS", (Vector2) { 0.5, 0.5 }, 55, 0, GREEN);

        if (IsMouseButtonPressed(0)) {
            *p_theme_button_state = 0;
            drawbackground = 0;
            selectblok = 0;
            selectbird = 1;
        }
    }
    else {
        DrawScaledCenteredText(MyWinter.WinterWindowed, "BIRDS", (Vector2) { 0.5, 0.5 }, 50, 0, RAYWHITE);
    }
    if (CheckCollisionPointRec(GetMousePosition(), BlockTextures)) {
        DrawScaledCenteredText(MyWinter.WinterPopupWindowed, "BLOCKS", (Vector2) { 0.7, 0.5 }, 55, 0, GREEN);

        if (IsMouseButtonPressed(0)) {
            *p_theme_button_state = 0;
            drawbackground = 0;
            selectbird = 0;
            selectblok = 1;
        }
    }
    else {
        DrawScaledCenteredText(MyWinter.WinterWindowed, "BLOCKS", (Vector2) { 0.7, 0.5 }, 50, 0, RAYWHITE);
    }


}

void ExecutePauseScreen(void)
{
    Vector2 Menutext = GetScaledCenteredTextCorner(MyWinter.WinterWindowed, "MENU", (Vector2) { 0.5, 0.9 }, 32, 0);
    Rectangle MenuT;
    MenuT.x = Menutext.x;
    MenuT.y = Menutext.y;
    MenuT.width = MeasureTextEx(MyWinter.WinterWindowed, "MENU", 50, 0).x;
    MenuT.height = MeasureTextEx(MyWinter.WinterWindowed, "MENU", 50, 0).y;

    Vector2 PauseText = GetScaledCenteredTextCorner(MyWinter.WinterWindowed, "Paused", (Vector2) { 0.5, 0.5 }, 50, 0);
    Rectangle PauseT;
    PauseT.x = PauseText.x;
    PauseT.y = PauseText.y;
    PauseT.width = MeasureTextEx(MyWinter.WinterWindowed, "Paused", 50, 0).x;
    PauseT.height = MeasureTextEx(MyWinter.WinterWindowed, "Paused", 50, 0).y;

    DrawBackgroundTexture(drawbackground);

    PauseSound(LoseS);


    if ((framesCounter / 30) % 2) 
    {
        DrawScaledCenteredText(MyWinter.WinterWindowed, "Paused", (Vector2) { 0.5, 0.5 }, 50, 0, WHITE);
    }

    DrawScaledCenteredText(MyWinter.WinterDetailW, TextFormat("SCORE:%i", score), (Vector2) { 0.5, 0.6 }, 32, 0, WHITE);
    DrawScaledCenteredText(MyWinter.WinterDetailW, TextFormat("HI-SCORE: %i", hiScore), (Vector2) { 0.5, 0.7 }, 32, 0, WHITE);

    DrawTextureEx(PlayButton, (Vector2) { GetScreenWidth() - (PlayButton.width + 10), 10 }, 0, 1, WHITE);
    DrawScaledCenteredText(MyWinter.WinterWindowed, "MENU", (Vector2) { 0.5, 0.9 }, 50, 0, WHITE);


    if (CheckCollisionPointRec(GetMousePosition(), MenuT) && IsMouseButtonPressed(0))
    {
        start_button_state = 0;

    }

    if (CheckCollisionPointRec(GetMousePosition(), PauseT) && IsMouseButtonPressed(0))
    {
        pause = !pause;

    }

}


void ExecuteLoseScreen(void)
{

    Vector2 AgainButtonCorner = GetScaledCenteredTextCorner(MyWinter.WinterDetailW, "Play Again", (Vector2) { 0.5, 0.5 }, 32, 0);
    Rectangle AgainT;
    AgainT.x = AgainButtonCorner.x;
    AgainT.y = AgainButtonCorner.y;
    AgainT.width = MeasureTextEx(MyWinter.WinterWindowed, "Play Again", 50, 0).x;
    AgainT.height = MeasureTextEx(MyWinter.WinterWindowed, "Play Again", 50, 0).y;


    DrawBackgroundTexture(drawbackground);



    DrawScaledCenteredText(MyWinter.WinterWindowed, "You Lost", (Vector2) { 0.5, 0.3 }, 50, 0, RED);

    if (CheckCollisionPointRec(GetMousePosition(), AgainT)) {
        DrawScaledCenteredText(MyWinter.WinterPopupWindowed, "Play Again", (Vector2) { 0.5, 0.5 }, 55, 0, GREEN);
    }
    else {
        DrawScaledCenteredText(MyWinter.WinterWindowed, "Play Again", (Vector2) { 0.5, 0.5 }, 50, 0, RAYWHITE);
    }


    DrawScaledCenteredText(MyWinter.WinterDetailW, TextFormat("SCORE:%i", score), (Vector2) { 0.5, 0.7 }, 32, 0, WHITE);
    DrawScaledCenteredText(MyWinter.WinterDetailW, TextFormat("HI-SCORE: %i", hiScore), (Vector2) { 0.5, 0.8 }, 32, 0, WHITE);
    DrawScaledCenteredText(MyWinter.WinterWindowed, "MENU", (Vector2) { 0.5, 0.9 }, 50, 0, WHITE);



    if (CheckCollisionPointRec(GetMousePosition(), AgainT) && IsMouseButtonPressed(0)) {

        InitGame();
        gameOver = false;
    }

    Vector2 Menutext = GetScaledCenteredTextCorner(MyWinter.WinterWindowed, "MENU", (Vector2) { 0.5, 0.9 }, 32, 0);
    Rectangle MenuT;
    MenuT.x = Menutext.x;
    MenuT.y = Menutext.y;
    MenuT.width = MeasureTextEx(MyWinter.WinterWindowed, "MENU", 50, 0).x;
    MenuT.height = MeasureTextEx(MyWinter.WinterWindowed, "MENU", 50, 0).y;

    if (CheckCollisionPointRec(GetMousePosition(), MenuT) && IsMouseButtonPressed(0))
    {
        start_button_state = 0;

    }

}
void DrawBackgroundTexture(int drawbackground)
{


    Vector2 ClassicButton = GetScaledCenteredTextCorner(MyWinter.WinterWindowed, "Classic", (Vector2) { 0.2, 0.3 }, 50, 0);
    Rectangle ClassicText;
    ClassicText.x = ClassicButton.x;
    ClassicText.y = ClassicButton.y;
    ClassicText.width = MeasureTextEx(MyWinter.WinterWindowed, "Classic", 50, 0).x;
    ClassicText.height = MeasureTextEx(MyWinter.WinterWindowed, "Classic", 50, 0).y;

    Vector2 CityButton = GetScaledCenteredTextCorner(MyWinter.WinterWindowed, "City", (Vector2) { 0.2, 0.4 }, 50, 0);
    Rectangle CityText;
    CityText.x = CityButton.x;
    CityText.y = CityButton.y;
    CityText.width = MeasureTextEx(MyWinter.WinterWindowed, "City", 50, 0).x;
    CityText.height = MeasureTextEx(MyWinter.WinterWindowed, "City", 50, 0).y;

    Vector2 DesertButton = GetScaledCenteredTextCorner(MyWinter.WinterWindowed, "City", (Vector2) { 0.2, 0.5 }, 50, 0);
    Rectangle DesertText;
    DesertText.x = DesertButton.x;
    DesertText.y = DesertButton.y;
    DesertText.width = MeasureTextEx(MyWinter.WinterWindowed, "Desert", 50, 0).x;
    DesertText.height = MeasureTextEx(MyWinter.WinterWindowed, "Desert", 50, 0).y;

    Vector2 SpaceButton = GetScaledCenteredTextCorner(MyWinter.WinterWindowed, "City", (Vector2) { 0.2, 0.6 }, 50, 0);
    Rectangle SpaceText;
    SpaceText.x = SpaceButton.x;
    SpaceText.y = SpaceButton.y;
    SpaceText.width = MeasureTextEx(MyWinter.WinterWindowed, "Desert", 50, 0).x;
    SpaceText.height = MeasureTextEx(MyWinter.WinterWindowed, "Desert", 50, 0).y;


    if (background_texture == 1)
    {
        DrawTextureEx(Classic, (Vector2) { 0, 0 }, 0, 1, WHITE);
        background_temp = Classic;
    }
    
    else if (background_texture == 2)
    {
        DrawTextureEx(City, (Vector2) { 0, 0 }, 0, 1, WHITE);
        background_temp = City;

    }
    else if (background_texture == 3)
    {
        DrawTextureEx(Desert, (Vector2) { 0, 0 }, 0, 1, WHITE);
        background_temp = Desert;


    }
    else if (background_texture == 4)
    {
        DrawTextureEx(Space, (Vector2) { 0, 0 }, 0, 1, WHITE);
        background_temp = Space;

    }
    



    if (drawbackground)
    {
        DrawTextureEx(ReturnButton, (Vector2) { 10, 10 }, 0, 1, WHITE);

        Rectangle ReturnBounds = { 10, 10, ReturnButton.width , ReturnButton.height };
        if (CheckCollisionPointRec(GetMousePosition(), ReturnBounds) && IsMouseButtonPressed(0)) {

            drawbackground = 0;
            selectbird = 0;
            selectblok = 0;
            theme_button_state = 1;
        }

        DrawScaledCenteredText(MyWinter.WinterTitleWindowed, "MAPS", (Vector2) { 0.3, 0.2 }, 100, 0, RAYWHITE);



        if (CheckCollisionPointRec(GetMousePosition(), ClassicText)) {
            DrawScaledCenteredText(MyWinter.WinterPopupWindowed, "Classic", (Vector2) { 0.2, 0.3 }, 55, 0, GREEN);

            if (IsMouseButtonPressed(0)) {

                background_texture = 1;
            }
        }
        else {
            DrawScaledCenteredText(MyWinter.WinterWindowed, "Classic", (Vector2) { 0.2, 0.3 }, 50, 0, RAYWHITE);
        }

        if (CheckCollisionPointRec(GetMousePosition(), CityText)) {
            DrawScaledCenteredText(MyWinter.WinterPopupWindowed, "City", (Vector2) { 0.2, 0.4 }, 55, 0, GREEN);

            if (IsMouseButtonPressed(0)) {

                background_texture = 2;
            }
        }
        else {
            DrawScaledCenteredText(MyWinter.WinterWindowed, "City", (Vector2) { 0.2, 0.4 }, 50, 0, RAYWHITE);
        }

        if (CheckCollisionPointRec(GetMousePosition(), DesertText)) {
            DrawScaledCenteredText(MyWinter.WinterPopupWindowed, "Desert", (Vector2) { 0.2, 0.5 }, 55, 0, GREEN);

            if (IsMouseButtonPressed(0)) {

                background_texture = 3;
            }
        }
        else {
            DrawScaledCenteredText(MyWinter.WinterWindowed, "Desert", (Vector2) { 0.2, 0.5 }, 50, 0, RAYWHITE);
        }

        if (CheckCollisionPointRec(GetMousePosition(), SpaceText)) {
            DrawScaledCenteredText(MyWinter.WinterPopupWindowed, "Space", (Vector2) { 0.2, 0.6 }, 55, 0, GREEN);

            if (IsMouseButtonPressed(0)) {

                background_texture = 4;
            }
        }
        else {
            DrawScaledCenteredText(MyWinter.WinterWindowed, "Space", (Vector2) { 0.2, 0.6 }, 50, 0, RAYWHITE);
        }

    }
}


void SelectBirdTexture(int selectbird)
{
    DrawBackgroundTexture(drawbackground);

    Vector2 BirdButton = GetScaledCenteredTextCorner(MyWinter.WinterWindowed, "Classic Bird", (Vector2) { 0.2, 0.3 }, 50, 0);
    Rectangle BirdText;
    BirdText.x = BirdButton.x;
    BirdText.y = BirdButton.y;
    BirdText.width = MeasureTextEx(MyWinter.WinterWindowed, "Classic Bird", 50, 0).x;
    BirdText.height = MeasureTextEx(MyWinter.WinterWindowed, "Classic Bird", 50, 0).y;

    Vector2 AstronautButton = GetScaledCenteredTextCorner(MyWinter.WinterWindowed, "Astronaut", (Vector2) { 0.2, 0.4 }, 50, 0);
    Rectangle AstronautText;
    AstronautText.x = AstronautButton.x;
    AstronautText.y = AstronautButton.y;
    AstronautText.width = MeasureTextEx(MyWinter.WinterWindowed, "Astronaut", 50, 0).x;
    AstronautText.height = MeasureTextEx(MyWinter.WinterWindowed, "Astronaut", 50, 0).y;

    Vector2 GhostButton = GetScaledCenteredTextCorner(MyWinter.WinterWindowed, "Ghost", (Vector2) { 0.2, 0.5 }, 50, 0);
    Rectangle GhostText;
    GhostText.x = GhostButton.x;
    GhostText.y = GhostButton.y;
    GhostText.width = MeasureTextEx(MyWinter.WinterWindowed, "Ghost", 50, 0).x;
    GhostText.height = MeasureTextEx(MyWinter.WinterWindowed, "Ghost", 50, 0).y;

    Vector2 FinnButton = GetScaledCenteredTextCorner(MyWinter.WinterWindowed, "Finn and Jake", (Vector2) { 0.2, 0.6 }, 50, 0);
    Rectangle FinnText;
    FinnText.x = FinnButton.x;
    FinnText.y = FinnButton.y;
    FinnText.width = MeasureTextEx(MyWinter.WinterWindowed, "Finn and Jake", 50, 0).x;
    FinnText.height = MeasureTextEx(MyWinter.WinterWindowed, "Finn and Jake", 50, 0).y;
    if (selectbird)
    {

        DrawTextureEx(ReturnButton, (Vector2) { 10, 10 }, 0, 1, WHITE);

        Rectangle ReturnBounds = { 10, 10, ReturnButton.width , ReturnButton.height };
        if (CheckCollisionPointRec(GetMousePosition(), ReturnBounds) && IsMouseButtonPressed(0)) {

            selectbird = 0;
            drawbackground = 0;
            selectblok = 0;
            theme_button_state = 1;
        }

        DrawScaledCenteredText(MyWinter.WinterTitleWindowed, "BIRDS", (Vector2) { 0.3, 0.2 }, 100, 0, RAYWHITE);

        if (CheckCollisionPointRec(GetMousePosition(), BirdText)) {
            DrawScaledCenteredText(MyWinter.WinterPopupWindowed, "Classic Bird", (Vector2) { 0.2, 0.3 }, 55, 0, GREEN);

            if (IsMouseButtonPressed(0)) {

                bird_texture = 1;
            }
        }
        else {
            DrawScaledCenteredText(MyWinter.WinterWindowed, "Classic Bird", (Vector2) { 0.2, 0.3 }, 50, 0, RAYWHITE);
        }

        if (CheckCollisionPointRec(GetMousePosition(), AstronautText)) {
            DrawScaledCenteredText(MyWinter.WinterPopupWindowed, "Astronaut", (Vector2) { 0.2, 0.4 }, 55, 0, GREEN);

            if (IsMouseButtonPressed(0)) {

                bird_texture = 2;
            }
        }
        else {
            DrawScaledCenteredText(MyWinter.WinterWindowed, "Astronaut", (Vector2) { 0.2, 0.4 }, 50, 0, RAYWHITE);
        }

        if (CheckCollisionPointRec(GetMousePosition(), GhostText)) {
            DrawScaledCenteredText(MyWinter.WinterPopupWindowed, "Ghost", (Vector2) { 0.2, 0.5 }, 55, 0, GREEN);

            if (IsMouseButtonPressed(0)) {

                bird_texture = 3;
            }
        }
        else {
            DrawScaledCenteredText(MyWinter.WinterWindowed, "Ghost", (Vector2) { 0.2, 0.5 }, 50, 0, RAYWHITE);
        }

        if (CheckCollisionPointRec(GetMousePosition(), FinnText)) {
            DrawScaledCenteredText(MyWinter.WinterPopupWindowed, "Finn and Jake", (Vector2) { 0.2, 0.6 }, 55, 0, GREEN);

            if (IsMouseButtonPressed(0)) {

                bird_texture = 4;
            }
        }
        else {
            DrawScaledCenteredText(MyWinter.WinterWindowed, "Finn and Jake", (Vector2) { 0.2, 0.6 }, 50, 0, RAYWHITE);
        }
    }

    if (bird_texture == 1)
    {
        texture = Bird;


    }
    else if (bird_texture == 2)
    {
        texture = Astronaut;

    }
    else if (bird_texture == 3)
    {
        texture = Ghost;

    }
    else if (bird_texture == 4)
    {
        texture = Finn;

    }
    
    if (selectbird)//seÁim ekran˝ iÁin
    {
        DrawTexture(texture, (GetScreenWidth() - texture.width) / 2, (GetScreenHeight() - texture.height) / 2, WHITE);
    }
}

void SelectBlockTexture(int selectblok)
{
    DrawBackgroundTexture(drawbackground);


    Vector2 ApartmentButton = GetScaledCenteredTextCorner(MyWinter.WinterWindowed, "Apartment", (Vector2) { 0.2, 0.3 }, 50, 0);
    Rectangle ApartmentText;
    ApartmentText.x = ApartmentButton.x;
    ApartmentText.y = ApartmentButton.y;
    ApartmentText.width = MeasureTextEx(MyWinter.WinterWindowed, "Apartment", 50, 0).x;
    ApartmentText.height = MeasureTextEx(MyWinter.WinterWindowed, "Apartment", 50, 0).y;

    Vector2 SpaceShipButton = GetScaledCenteredTextCorner(MyWinter.WinterWindowed, "Space Ship", (Vector2) { 0.2, 0.4 }, 50, 0);
    Rectangle SpaceShipText;
    SpaceShipText.x = SpaceShipButton.x;
    SpaceShipText.y = SpaceShipButton.y;
    SpaceShipText.width = MeasureTextEx(MyWinter.WinterWindowed, "Space Ship", 50, 0).x;
    SpaceShipText.height = MeasureTextEx(MyWinter.WinterWindowed, "Space Ship", 50, 0).y;

    Vector2 GrayBlockButton = GetScaledCenteredTextCorner(MyWinter.WinterWindowed, "Gray Block", (Vector2) { 0.2, 0.5 }, 50, 0);
    Rectangle GrayBlockText;
    GrayBlockText.x = GrayBlockButton.x;
    GrayBlockText.y = GrayBlockButton.y;
    GrayBlockText.width = MeasureTextEx(MyWinter.WinterWindowed, "Gray Block", 50, 0).x;
    GrayBlockText.height = MeasureTextEx(MyWinter.WinterWindowed, "Gray Block", 50, 0).y;

    if (selectblok)
    {

        DrawTextureEx(ReturnButton, (Vector2) { 10, 10 }, 0, 1, WHITE);

        Rectangle ReturnBounds = { 10, 10, ReturnButton.width , ReturnButton.height };
        if (CheckCollisionPointRec(GetMousePosition(), ReturnBounds) && IsMouseButtonPressed(0)) {

            selectbird = 0;
            drawbackground = 0;
            selectblok = 0;
            theme_button_state = 1;
        }

        DrawScaledCenteredText(MyWinter.WinterTitleWindowed, "BLOKS", (Vector2) { 0.3, 0.2 }, 100, 0, RAYWHITE);



        if (CheckCollisionPointRec(GetMousePosition(), ApartmentText)) {
            DrawScaledCenteredText(MyWinter.WinterPopupWindowed, "Apartment", (Vector2) { 0.2, 0.3 }, 55, 0, GREEN);

            if (IsMouseButtonPressed(0)) {

                block_texture = 1;
            }
        }
        else {
            DrawScaledCenteredText(MyWinter.WinterWindowed, "Apartment", (Vector2) { 0.2, 0.3 }, 50, 0, RAYWHITE);
        }

        if (CheckCollisionPointRec(GetMousePosition(), SpaceShipText)) {
            DrawScaledCenteredText(MyWinter.WinterPopupWindowed, "Space Ship", (Vector2) { 0.2, 0.4 }, 55, 0, GREEN);

            if (IsMouseButtonPressed(0)) {

                block_texture = 2;
            }
        }
        else {
            DrawScaledCenteredText(MyWinter.WinterWindowed, "Space Ship", (Vector2) { 0.2, 0.4 }, 50, 0, RAYWHITE);
        }
        if (CheckCollisionPointRec(GetMousePosition(), GrayBlockText)) {
            DrawScaledCenteredText(MyWinter.WinterPopupWindowed, "Gray Block", (Vector2) { 0.2, 0.5 }, 55, 0, GREEN);

            if (IsMouseButtonPressed(0)) {

                block_texture = 3;
            }
        }
        else {
            DrawScaledCenteredText(MyWinter.WinterWindowed, "Gray Block", (Vector2) { 0.2, 0.5 }, 50, 0, RAYWHITE);
        }
    }

    if (block_texture == 1)
    {
        Temp1 = Apartment;
        Temp2 = Apartment2;
    }

    else if (block_texture == 2)
    {
        Temp1 = SpaceShip;
        Temp2 = SpaceShip2;
    }

    else if (block_texture == 3)
    {
        Temp1 = GrayBlock;
        Temp2 = GrayBlock;
    }

    //Seçilen blogu gösteriyor
    DrawTexture(Temp1, (GetScreenWidth() - Temp1.width) / 2, (GetScreenHeight() - Temp1.height), WHITE);

}


void ScrollingBackground(void)
{
    if (background_texture == 4)
    {
        DrawTextureEx(background_temp, (Vector2) { 0, 0 }, 0.0f, 1.0f, WHITE);

    }
    
    else if (background_texture == 3)
    {
        DrawTextureEx(background_temp, (Vector2) { 0, 0 }, 0.0f, 1.0f, WHITE);


    }

    else if (background_texture == 2)
    {

        DrawTextureEx(City, (Vector2) { scrollingFore, 0 }, 0.0f, 1.0f, WHITE);


        DrawTextureEx(City2, (Vector2) { (background_temp.width * 1) + scrollingFore, 0 }, 0.0f, 1.0f, WHITE);
        DrawTextureEx(City2, (Vector2) { (background_temp.width * 2) + scrollingFore, 0 }, 0.0f, 1.0f, WHITE);

        

    }

    else if (block_texture == 1)
    {
        DrawTextureEx(foreground, (Vector2) { scrollingFore, 392 }, 0.0f, 1.0f, WHITE);
        DrawTextureEx(foreground, (Vector2) { foreground.width * 1 + scrollingFore, 392 }, 0.0f, 1.0f, WHITE);
        DrawTextureEx(foreground, (Vector2) { foreground.width * 2 + scrollingFore, 392 }, 0.0f, 1.0f, WHITE);


        DrawTextureEx(background, (Vector2) { scrollingBack, 0 }, 0.0f, 1.0f, WHITE);

        DrawTextureEx(background2, (Vector2) { background.width * 1 + scrollingBack, 0 }, 0.0f, 1.0f, WHITE);
        DrawTextureEx(background2, (Vector2) { background.width * 2 + scrollingBack, 0 }, 0.0f, 1.0f, WHITE);

    }
}


//kuşun açısı
void BirdRotation(Texture2D texture, int rotation)
{

    int frameWidth = texture.width;
    int frameHeight = texture.height;

    Rectangle sourceRec = { 0, 0, texture.width, texture.height };
    Rectangle destRec = { bird.position.x, bird.position.y , texture.width, texture.height };
    Vector2 origin = { texture.width / 2, texture.height / 2 };


    DrawTexturePro(texture, sourceRec, destRec, origin, rotation, WHITE);


}


void ReverseMode(void)
{
    if (rotation >= 45)
    {
        rotation = 45;
    }

    if (rotation <= -45)
    {
        rotation = -45;
    }



    if (modOn)
    {
        if (IsKeyDown(KEY_SPACE) && !gameOver)
        {
            if (score >= 800 * modeCounter + 400)
            {

                bird.position.y += 5;
                rotation = 45;
                reverse_icon = 1;
            }
            else
            {

                bird.position.y -= 5;
                rotation = -45;
                reverse_icon = 0;
            }


        }
        else {
            if (score >= 800 * modeCounter + 400)
            {

                bird.position.y -= 3;
                rotation -= 3;

            }
            else
            {

                bird.position.y += 3;
                rotation += 3;

            }

            if (score == (800 * (modeCounter + 1)))
            {
                modeCounter++;
            }

        }

    }
    else
    {
        if (IsKeyDown(KEY_SPACE) && !gameOver)
        {
            bird.position.y -= 5;
            rotation = -45;
        }

        else
        {

            bird.position.y += 3;
            rotation += 3;

        }
    }

}


// Initialize game variables
void InitGame(void)
{
    SetTargetFPS(60);

    MyWinter.WinterTitleWindowed = LoadFontEx("source/Winter Storm.ttf", 100, NULL, 0);
    MyWinter.WinterWindowed = LoadFontEx("source/Winter Storm.ttf", 50, NULL, 0);
    MyWinter.WinterPopupWindowed = LoadFontEx("source/Winter Storm.ttf", 55, NULL, 0);
    MyWinter.WinterDetailW = LoadFontEx("source/Winter Storm.ttf", 32, NULL, 0);

    ReturnButton = LoadTexture("source/returnicon.png");
    PlayButton = LoadTexture("source/play_icon.png");
    PauseButton = LoadTexture("source/pause_icon.png");
    ReverseIcon = LoadTexture("source/reverse.png");

    Classic = LoadTexture("source/sbackground.png");
    background = LoadTexture("source/sky.png");
    background2 = LoadTexture("source/skywithoutsun.png");

    foreground = LoadTexture("source/ground.png");

    City = LoadTexture("source/city.png");
    City2 = LoadTexture("source/secondcity.png");

    Space = LoadTexture("source/space.png");
    Desert = LoadTexture("source/desert.png");
    Gray = LoadTexture("source/gray.png");

    Bird = LoadTexture("source/bird1.png");
    Astronaut = LoadTexture("source/astronaut.png");
    Ghost = LoadTexture("source/ghost.png");
    Finn = LoadTexture("source/finn.png");

    Apartment = LoadTexture("source/apartment.png");
    Apartment2 = LoadTexture("source/apartment2.png");
    SpaceShip = LoadTexture("source/space_ship.png");
    SpaceShip2 = LoadTexture("source/space_ship2.png");
    GrayBlock = LoadTexture("source/grayblock.png");

    PointS = LoadSound("source/ping.mp3");
    LoseS = LoadSound("source/beeps.mp3");

    GameMusic = LoadMusicStream("source/Lost Woods.mp3");


    bird.radius = Bird.width / 2;
    bird.position = (Vector2){ 80, screenHeight / 2 - Bird.width };
    tubesSpeedX = 2;

    for (int i = 0; i < MAX_TUBES; i++)
    {
        tubesPos[i].x = 450 + 500 * i;
        tubesPos[i].y = -GetRandomValue(0, 350);
    }

    for (int i = 0; i < MAX_TUBES * 2; i += 2)
    {
        tubes[i].rec.x = tubesPos[i / 2].x;
        tubes[i].rec.y = tubesPos[i / 2].y;
        tubes[i].rec.width = TUBES_WIDTH;
        tubes[i].rec.height = 375;

        tubes[i + 1].rec.x = tubesPos[i / 2].x;
        tubes[i + 1].rec.y = 900 + tubesPos[i / 2].y - 350;
        tubes[i + 1].rec.width = TUBES_WIDTH;
        tubes[i + 1].rec.height = 375;

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



        scrollingBack -= 0.2;
        scrollingFore -= 1.0;


        if (scrollingFore <= -background_temp.width * 2) scrollingFore = -background_temp.width;


        framesCounter++;

        Rectangle PauseButtonBounds = { GetScreenWidth() - PauseButton.width - 10, 10, PauseButton.width , PauseButton.height }; // ›kon s˝n˝rlar˝n˝ belirle

        if (IsKeyPressed('P') || (CheckCollisionPointRec(GetMousePosition(), PauseButtonBounds) && IsMouseButtonPressed(0))) pause = !pause;

        if (!pause)
        {
            for (int i = 0; i < MAX_TUBES; i++) tubesPos[i].x -= tubesSpeedX + (0.08 * i);

            for (int i = 0; i < MAX_TUBES * 2; i += 2)
            {
                tubes[i].rec.x = tubesPos[i / 2].x;
                tubes[i + 1].rec.x = tubesPos[i / 2].x;
            }


            ReverseMode();


            // Çaprışma kontrolü
            for (int i = 0; i < MAX_TUBES * 2; i++)
            {

                // Alt sınır kontrolü
                if (bird.position.y + bird.radius / 2 >= screenHeight) {

                    gameOver = true;
                    pause = false;

                }

                // üst sınır kontrolü
                if (bird.position.y - bird.radius / 2 <= 0) {

                    gameOver = true;
                    pause = false;

                }


                if (CheckCollisionCircleRec(bird.position, bird.radius, tubes[i].rec))
                {

                    gameOver = true;
                    pause = false;

                }
                else if ((tubesPos[i / 2].x < bird.position.x) && tubes[i / 2].active && !gameOver)//sonra bak ko˛ullar yanl˝˛
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


        SelectBlockTexture(selectblok);
        SelectBirdTexture(selectbird);
        ScrollingBackground();

        BirdRotation(texture, rotation);


        // Draw tubes
        for (int i = 0; i < MAX_TUBES; i++)
        {

            DrawTextureEx(Temp2, (Vector2) { tubes[i * 2].rec.x, tubes[i * 2].rec.y }, 0, 1, WHITE);
            DrawTextureEx(Temp1, (Vector2) { tubes[i * 2 + 1].rec.x, tubes[i * 2 + 1].rec.y }, 0, 1, WHITE);
        }

        // Score moment
        if (score_flag)
        {
            PlaySound(PointS);
            score_flag = false;
        }
        PlaySound(LoseS);

        if (((framesCounter / 30) % 2) && reverse_icon && modOn) {
            DrawTextureEx(ReverseIcon, (Vector2) { 10, 150 }, 0, 1, WHITE);
        }

        DrawScaledCenteredText(MyWinter.WinterDetailW, TextFormat("%i", score), (Vector2) { 0.1, 0.1 }, 32, 0, BLACK);
        DrawScaledCenteredText(MyWinter.WinterDetailW, TextFormat("HI-SCORE: %i", hiScore), (Vector2) { 0.1, 0.2 }, 32, 0, BLACK);
        DrawTextureEx(PauseButton, (Vector2) { GetScreenWidth() - (PlayButton.width + 10), 10 }, 0, 1, WHITE);


    }

    else if (gameOver) {
        modeCounter = 0;
        ExecuteLoseScreen();
    }
    if (pause) ExecutePauseScreen();

}


void UnloadGame(void)
{
    // Arka plan resmi
    if (Classic.id > 0) UnloadTexture(Classic);
    if (background.id > 0) UnloadTexture(background);
    if (background2.id > 0) UnloadTexture(background2);
    if (foreground.id > 0) UnloadTexture(foreground);

    if (City.id > 0) UnloadTexture(City);
    if (City2.id > 0) UnloadTexture(City2);


    if (Space.id > 0) UnloadTexture(Space);
    if (Desert.id > 0) UnloadTexture(Desert);
    if (Gray.id > 0) UnloadTexture(Gray);


    if (Apartment.id > 0) UnloadTexture(Apartment);
    if (Apartment2.id > 0) UnloadTexture(Apartment2);
    if (SpaceShip.id > 0) UnloadTexture(SpaceShip);
    if (SpaceShip2.id > 0) UnloadTexture(SpaceShip2);
    if (GrayBlock.id > 0) UnloadTexture(GrayBlock);


    // Kuş resmleri
    if (Bird.id > 0) UnloadTexture(Bird);
    if (Astronaut.id > 0) UnloadTexture(Astronaut);
    if (Ghost.id > 0) UnloadTexture(Ghost);
    if (Finn.id > 0) UnloadTexture(Finn);


    if (PlayButton.id > 0) UnloadTexture(PlayButton);
    if (ReturnButton.id > 0) UnloadTexture(ReturnButton);
    if (PauseButton.id > 0) UnloadTexture(PauseButton);
    if (ReverseIcon.id > 0) UnloadTexture(ReverseIcon);


    UnloadSound(LoseS);
    UnloadSound(PointS);


    if (IsMusicStreamPlaying(GameMusic))
    {
        StopMusicStream(GameMusic);
        UnloadMusicStream(GameMusic);
    }

    // Yazı tipleri
    if (MyWinter.WinterTitleWindowed.texture.id > 0) UnloadFont(MyWinter.WinterTitleWindowed);
    if (MyWinter.WinterWindowed.texture.id > 0) UnloadFont(MyWinter.WinterWindowed);
    if (MyWinter.WinterPopupWindowed.texture.id > 0) UnloadFont(MyWinter.WinterPopupWindowed);
    if (MyWinter.WinterDetailW.texture.id > 0) UnloadFont(MyWinter.WinterDetailW);


    CloseWindow();
}



// Update and Draw (one frame)
void UpdateDrawFrame(void)
{
    UpdateGame();

    DrawGame();  
}

