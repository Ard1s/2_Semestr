#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "raylib.h"
#include "func.h"
#define MAX_INPUT_CHARS     30

int main(int argc, char* argv[])
{
	uint8_t* result;
	const int screenWidth = 800;
	const int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "Hash_Utility");
	char name[MAX_INPUT_CHARS + 1] = "\0";
	int letterCount = 0;

	Rectangle textBox = { screenWidth / 6.0f - 100, 180, 750, 50 };
	bool mouseOnText = false;

	int framesCounter = 0;
	long long HASH = 0;
	char Hash[100] = { 0 };
	SetTargetFPS(30);
	while (!WindowShouldClose()) 
	{
		BeginDrawing();
		ClearBackground(BLUE);

		DrawText("Hover the mouse over the window", 240, 140, 20, YELLOW);

		DrawRectangleRec(textBox, PINK);
		if (mouseOnText) DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, RED);
		else DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, BLACK);

		DrawText(name, (int)textBox.x + 5, (int)textBox.y + 8, 40, MAROON);

		DrawText(TextFormat("Enter values: %i/%i", letterCount, MAX_INPUT_CHARS), 315, 250, 20, YELLOW);
		store(letterCount, HASH);
		print_hash(Hash);
		find(HASH);


		EndDrawing();
	}
	CloseWindow();
	return 0;
}







