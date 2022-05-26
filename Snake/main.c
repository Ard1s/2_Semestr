#define _CRT_SECURE_NO_WARNINGS

#include <math.h>
#include <raylib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

#define CANVAS_WIDTH 240
#define CANVAS_HEIGHT 120

#define CELL_WIDTH 10   
#define CELL_HEIGHT 10  

#define EAT_WIDTH 6
#define EAT_HEIGHT 6

#define FIELD_WIDTH 24   
#define FIELD_HEIGHT 12  

#define LVL_COUNT 5

#define COOL_DOWN_BEFORE_START 1  

float cool_down = 0;

typedef struct Coordinates_ 
{
    int x;
    int y;
} Coordinates;

const short LVL[LVL_COUNT][FIELD_HEIGHT][FIELD_WIDTH] = 
{
    // LVL 0
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    // LVL 1

      1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
      1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
      1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
      1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
      1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
      1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
      1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,

      // LVL 2
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

      // LVL 3
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
      1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
      1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
      0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
      1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
      1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
      0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
      1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
      1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
      0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

      // LVL 4
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0,
      0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0,
      0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};


const Coordinates SNAKE_SPAWNS[LVL_COUNT] = 
{
    {6, 6}, {6, 6}, {16, 4}, {4, 0}, {4, 0},
};

const int DIFFICULTY_COUNT = 3;
const char* const DIFFICULTY_NAMES[] = { "Speed: Slow", "Speed: Normal",
                                        "Speed: Speedrun" };
const float DIFFICULTY_SPEEDS[] = { 0.2f, 0.1f, 0.05f };
int difficulty = 0;

const Vector2 ZERO_VEC = { 0, 0 };
RenderTexture2D canvas;

typedef struct SnakeNode_ 
{
    int32_t lifetime;
    bool eat_inside;
} SnakeNode;

typedef struct Snake_ 
{
    int dir_x;  
    int dir_y;  
    int next_dir_x;
    int next_dir_y;
    int length;
    int pos_x;
    int pos_y;
    float speed;                 
    float last_step_updated_at;  
    bool has_changed_dir;
    bool has_eaten;
} Snake;

typedef struct Food_ 
{
    int x;
    int y;
} Food;

void GoToSelectLevel();
void GoToGame();

int current_lvl = 0;
bool is_game_over = false;
Food food = { -1, -1 };
SnakeNode snake_body[FIELD_WIDTH][FIELD_HEIGHT];
Snake snake;

void (*Draw)(void);
void (*Update)(void);

void InitSnake() {
    for (int i = 0; i < snake.length; i++) 
    {
        int x = snake.pos_x - snake.dir_x * i;
        int y = snake.pos_y - snake.dir_y * i;
        snake_body[x][y].lifetime = snake.length - i;
    }
}

void SpawnFood() 
{    
    int x;
    int y;
    do {
        x = GetRandomValue(0, FIELD_WIDTH - 1);
        y = GetRandomValue(0, FIELD_HEIGHT - 1);
    } while (snake_body[x][y].lifetime > 0 || LVL[current_lvl][y][x] > 0);
    TraceLog(LOG_INFO, "Spawn food at [%d,%d]", x, y);
    food.x = x;
    food.y = y;
}

void Setup() 
{
    cool_down = 0;
    snake.dir_x = 1;
    snake.dir_y = 0;
    snake.next_dir_x = 1;
    snake.next_dir_y = 0;
    snake.length = 2;
    snake.pos_x = SNAKE_SPAWNS[current_lvl].x;
    snake.pos_y = SNAKE_SPAWNS[current_lvl].y;
    snake.last_step_updated_at = 0;
    snake.has_eaten = false;
    snake.speed = DIFFICULTY_SPEEDS[difficulty];
    is_game_over = false;
    for (int i = 0; i < FIELD_WIDTH; i++) 
    {
        for (int j = 0; j < FIELD_HEIGHT; j++) 
        {
            snake_body[i][j].lifetime = 0;
            snake_body[i][j].eat_inside = false;
        }
    }

    InitSnake();
    SpawnFood();
}

void DrawWallBody(int i, int j) 
{
    if (LVL[current_lvl][j][i] == 0) 
    {
        return;
    }

    DrawRectangle(i * CELL_WIDTH, j * CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT,
        BLACK);
}

void DrawSnakeBody(int i, int j) 
{
    if (snake_body[i+1][j].lifetime < 1) 
    {
        return;
    }
    
    Texture2D body = LoadTexture("C:/Users/nasty/source/repos/Snake_/Snake_/radar.png");
    DrawTextureV(body, (Vector2) {i* CELL_WIDTH, j* CELL_HEIGHT }, WHITE);
    /*DrawRectangle(i * CELL_WIDTH, j * CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT,
        GREEN);*/
}

void DrawSnakeHead() 
{
    Texture2D snakeHead = LoadTexture("C:/Users/nasty/source/repos/Snake_/Snake_/snakes.png");
    DrawTextureV(snakeHead, (Vector2) {snake.pos_x* CELL_WIDTH, snake.pos_y* CELL_HEIGHT }, WHITE);
    /*DrawRectangle(snake.pos_x * CELL_WIDTH, snake.pos_y * CELL_HEIGHT, CELL_WIDTH,
        CELL_HEIGHT, DARKGREEN);*/
}

void DrawGameMatrix() 
{
    for (int i = 0; i < FIELD_WIDTH; i++) 
    {
        for (int j = 0; j < FIELD_HEIGHT; j++) 
        {
            DrawSnakeBody(i, j);
            DrawWallBody(i, j);
        }
    }
    DrawSnakeHead();
}

void DrawFood() 
{
    int dw = (CELL_WIDTH - EAT_WIDTH) / 2;
    int dh = (CELL_HEIGHT - EAT_HEIGHT) / 2;
    Texture2D apple = LoadTexture("C:/Users/nasty/source/repos/Snake_/Snake_/scare.png");
    DrawTextureV(apple, (Vector2) {food.x* CELL_WIDTH + dw, food.y* CELL_HEIGHT + dh}, WHITE);
}

void CheckFood() 
{
    if (snake.pos_x == food.x && snake.pos_y == food.y) 
    {
        snake.length++;
        snake.has_eaten = true;
        SpawnFood();
    }
}

void CheckCollisionWithWall() 
{
    if (LVL[current_lvl][snake.pos_y][snake.pos_x] > 0) 
    {
        is_game_over = true;
    }
}

void CheckBack() 
{
    if (snake_body[snake.pos_x][snake.pos_y].lifetime > 0) 
    {
        is_game_over = true;
    }
}

void MoveSnake() 
{
    snake.last_step_updated_at += GetFrameTime();
    if (snake.last_step_updated_at >= snake.speed) 
    {
        snake.last_step_updated_at = 0;
    }
    else 
    {
        return;
    }

    if (snake.has_eaten) 
    {
        snake.has_eaten = false;
    }
    else {
        for (int i = 0; i < FIELD_WIDTH; i++) 
        {
            for (int j = 0; j < FIELD_HEIGHT; j++) 
            {
                if (snake_body[i][j].lifetime > 0) 
                {
                    snake_body[i][j].lifetime--;
                }
            }
        }
    }

    snake.dir_x = snake.next_dir_x;
    snake.dir_y = snake.next_dir_y;
    snake.pos_x += snake.dir_x;
    snake.pos_y += snake.dir_y;

    if (snake.pos_x >= FIELD_WIDTH) 
    {
        snake.pos_x = 0;
    }
    if (snake.pos_x < 0) 
    {
        snake.pos_x = FIELD_WIDTH - 1;
    }
    if (snake.pos_y >= FIELD_HEIGHT) 
    {
        snake.pos_y = 0;
    }
    if (snake.pos_y < 0) 
    {
        snake.pos_y = FIELD_HEIGHT - 1;
    }

    CheckBack();
    CheckCollisionWithWall();
    snake_body[snake.pos_x][snake.pos_y].lifetime = snake.length;
}

void DrawGame() 
{
    DrawFood();
    DrawGameMatrix();

    if (is_game_over) 
    {
        DrawText("You've lost", 2, CANVAS_HEIGHT / 2, 20, PINK);
        DrawText("Press F to restart game", 2, CANVAS_HEIGHT / 2 + 20, 12, PINK);
    }
}

void ControlSnake() 
{
    if ((snake.dir_y == 0) && (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))) 
    {
        snake.next_dir_y = -1;
        snake.next_dir_x = 0;
        return;
    }
    if ((snake.dir_y == 0) && (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S))) 
    {
        snake.next_dir_y = 1;
        snake.next_dir_x = 0;
        return;
    }
    if ((snake.dir_x == 0) && (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A))) 
    {
        snake.next_dir_y = 0;
        snake.next_dir_x = -1;
        return;
    }
    if ((snake.dir_x == 0) && (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D))) 
    {
        snake.next_dir_y = 0;
        snake.next_dir_x = 1;
        return;
    }
}

void UpdateGame() 
{
    if (is_game_over) 
    {
        if (IsKeyPressed(KEY_F)) 
        {
            GoToSelectLevel();
        }
        return;
    }
    if (IsKeyPressed(KEY_R)) 
    {
        GoToSelectLevel();
        return;
    }

    if (IsKeyPressed(KEY_ENTER)) 
    {
        cool_down = 0;
        current_lvl++;
        if (current_lvl < 0) {
            current_lvl = LVL_COUNT - 1;
        }
        if (current_lvl >= LVL_COUNT) 
        {
            current_lvl = 0;
        }
    }

    if (cool_down < COOL_DOWN_BEFORE_START) 
    {
        cool_down += GetFrameTime();
        return;
    }

    MoveSnake();
    CheckFood();
    ControlSnake();
}

Rectangle GetCanvasTarget() 
{
    float sh = (float)GetScreenHeight();
    float sw = (float)GetScreenWidth();
    float scale = fminf(sh / CANVAS_HEIGHT, sw / CANVAS_WIDTH);
    Rectangle rec = { 0, 0, CANVAS_WIDTH * scale, CANVAS_HEIGHT * scale };
    return rec;
}

void GoToGame() 
{
    Draw = DrawGame;
    Update = UpdateGame;
    Setup();
}

void DrawSelectLevel() 
{
    DrawText("LEVEL: ", 4, 4, 20, PINK);
    DrawText("press UP or Down", 4, 24, 12, PINK);

    char buffer[3];  
    sprintf(buffer, "%d", current_lvl);
    DrawText(buffer, 84, 4, 20, PINK);

    DrawText(DIFFICULTY_NAMES[difficulty], 4, 42, 20, PINK);
    DrawText("press LEFT or RIGHT", 4, 62, 12, PINK);

    DrawText("press ENTER to start", 4, 92, 12, PINK);
}

void UpdateSelectLevel() 
{
    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) 
    {
        current_lvl--;
    }
    else if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) 
    {
        current_lvl++;
    }
    if (current_lvl < 0) 
    {
        current_lvl = LVL_COUNT - 1;
    }
    if (current_lvl >= LVL_COUNT) 
    {
        current_lvl = 0;
    }

    if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) 
    {
        difficulty--;
    }
    else if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) 
    {
        difficulty++;
    }
    if (difficulty < 0) 
    {
        difficulty = DIFFICULTY_COUNT - 1;
    }
    if (difficulty >= DIFFICULTY_COUNT) 
    {
        difficulty = 0;
    }

    if (IsKeyPressed(KEY_ENTER)) 
    {
        GoToGame();
    }
}

void GoToSelectLevel() 
{
    Draw = DrawSelectLevel;
    Update = UpdateSelectLevel;
}

void GameLoop() 
{
    BeginDrawing();
    ClearBackground(WHITE);

    BeginTextureMode(canvas);
    ClearBackground(YELLOW);
    Draw();
    EndTextureMode();

    Rectangle canvas_field = { 0, 0, (float)canvas.texture.width,
                              -(float)canvas.texture.height };
    DrawTexturePro(canvas.texture, canvas_field, GetCanvasTarget(), ZERO_VEC,
        0.0f, WHITE);
    EndDrawing();
    Update();
}

int main() 
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(CANVAS_WIDTH * 2, CANVAS_HEIGHT * 2, "Snake");
    SetTargetFPS(30);
    SetTextureFilter(GetFontDefault().texture, TEXTURE_FILTER_POINT);
    canvas = LoadRenderTexture(CANVAS_WIDTH, CANVAS_HEIGHT);
    SetTextureFilter(canvas.texture, TEXTURE_FILTER_POINT);

    Setup();
    GoToSelectLevel();

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(GameLoop, 0, 1);
#else
    while (!WindowShouldClose()) 
    {
        GameLoop();
    }
#endif

    CloseWindow();

    return 0;
}