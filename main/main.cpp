#include "raylib.h"
#include <math.h>

#define MAX_BUILDINGS   100

void DrawCustomCursor()
{
    float cursor_size = 5.0f;
    Rectangle rec = { (float) GetMouseX() - cursor_size / 2
                    , (float) GetMouseY() - cursor_size / 2
                    , cursor_size, cursor_size };
    DrawRectangleRec(rec, BLACK);
    DrawRectangleLinesEx(rec, 1, WHITE);
}
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Bullet hand");

    Rectangle player = { 400, 280, 40, 40 };
    int spacing = 0;


    Image hand_free_img = LoadImage("assets/hand_free.png");  // Load image data into CPU memory (RAM)
    Texture2D hand_free_tex = LoadTextureFromImage(hand_free_img);  // Image converted to texture, GPU memory (RAM -> VRAM)
    UnloadImage(hand_free_img);                               // Unload image data from CPU memory (RAM)
    // UnloadTexture(hand_free_tex);                           // Unload texture from GPU memory (VRAM)

    Image hand_grab_img = LoadImage("assets/hand_grab.png");  // Load image data into CPU memory (RAM)
    Texture2D hand_grab_tex = LoadTextureFromImage(hand_grab_img);  // Image converted to texture, GPU memory (RAM -> VRAM)
    UnloadImage(hand_grab_img);                               // Unload image data from CPU memory (RAM)
    // UnloadTexture(hand_grab_tex);                           // Unload texture from GPU memory (VRAM)

    // image = LoadImageFromTexture(texture);            // Load image from GPU texture (VRAM -> RAM)

    // texture = LoadTextureFromImage(image);            // Recreate texture from retrieved image data (RAM -> VRAM)
    // UnloadImage(image);


    Camera2D camera = { 0 };
    camera.target = (Vector2){ player.x + 20.0f, player.y + 20.0f };
    camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    HideCursor();

    SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // Player movement
        if (IsKeyDown(KEY_RIGHT)) player.x += 2;
        else if (IsKeyDown(KEY_LEFT)) player.x -= 2;

        if (IsKeyDown(KEY_DOWN)) player.y += 2;
        else if (IsKeyDown(KEY_UP)) player.y -= 2;

        if (IsKeyDown(KEY_MINUS) && camera.zoom > 0.5) camera.zoom -= 0.1;
        else if (IsKeyDown(KEY_EQUAL) && camera.zoom < 5) camera.zoom += 0.1;

        // Camera target follows player
        camera.target = (Vector2){ player.x + 20, player.y + 20 };

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(DARKGRAY);

            BeginMode2D(camera);

                Vector2 fd = {12, 12};

                int hand_shift = 0.0;
                DrawTextureEx( IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? hand_grab_tex : hand_free_tex
                             , {(float) GetMouseX(), (float) GetMouseY() + hand_shift }
                             , 0, 0.3, WHITE);

            EndMode2D();

            // DrawCustomCursor();

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
