#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 600


int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "MAN");
    SetTargetFPS(60);
    

    Texture2D man = LoadTexture("C:/Users/nasty/source/repos/2D_Animation/2D_Animation/man.png");
    float frameWidth = (float)(man.width / 3);
    int maxFrames = (int)(man.width / (int)frameWidth);
    Vector2 man_vector = { 100, 100 };

    float timer = 0.0f;
    int frame = 0;

    while (!WindowShouldClose(KEY_ESCAPE))
    {
        BeginDrawing();
        ClearBackground(DARKGREEN);

        timer += GetFrameTime();
        if (timer >= 0.2f)
        {
            timer = 0.0f;
            frame += 1;
        }

        frame = frame % maxFrames;
        printf_s("%d\n", frame);
        Rectangle man_field = { (frameWidth * frame), 0, (float)frameWidth, (float)man.height };

        DrawText("LOOK AT THE MAN!", 450, 500, 30, BLACK);
        DrawTextureRec(
            man,
            man_field,
            man_vector,
            RAYWHITE);

        EndDrawing();

    }

    CloseWindow();

    return 0;
}