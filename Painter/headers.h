#pragma once
#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
#include<windows.h>

void gotoxy(int, int);
void color(char[]);
void freeColor();
void loading();
void clear();


void clear() 
{
    system("cls");
}


void gotoxy(int x, int y) 
{
    COORD coord;
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(handle, coord);
}


void color(char color_name[20]) 
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    int color_code;
    if (color_name == "BLACK")
        color_code = 0;
    else if (color_name == "BLUE")
        color_code = 1;
    else if (color_name == "GREEN")
        color_code = 2;
    else if (color_name == "AQUABLUE")
        color_code = 3;
    else if (color_name == "RED")
        color_code = 4;
    else if (color_name == "PURPLE")
        color_code = 5;
    else if (color_name == "YELLOW")
        color_code = 6;
    else if (color_name == "WHITE")
        color_code = 7;
    else if (color_name == "GREY")
        color_code = 8;
    else if (color_name == "LIGHTBLUE")
        color_code = 9;
    else if (color_name == "LIGHTGREEN")
        color_code = 10;
    else if (color_name == "LIGHTAQUA")
        color_code = 11;
    else if (color_name == "LIGHTRED")
        color_code = 12;
    else if (color_name == "LIGHTPURPLE")
        color_code = 13;
    else if (color_name == "LIGHTYELLOW")
        color_code = 14;
    else if (color_name == "BRIGHTWHITE")
        color_code = 15;
    else
        color_code = 7;
    SetConsoleTextAttribute(handle, color_code);
}


void freeColor() 
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, 7);
}


void loading() 
{
    int size, delay;
    gotoxy(30, 14);
    printf("Loading....");
    gotoxy(30, 16);
    color("GREEN");
    for (size = 1; size <= 20; size++) 
    {
        printf("%c", 222);
        for (delay = 0; delay <= 10000000; delay++) {}
    }
}