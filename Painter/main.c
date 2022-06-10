#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include "headers.h"


#define UP 74
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define space 32

int x = 10, y = 10;
void boarder();
void clearWorkSpace();
void printControls();

int main() 
{
    int color_code = 7;
    char ch = 222;
    system("gcc header.h");
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    clear();
    boarder();
    gotoxy(50, 20);
    printf("W E L C O M E");
    _getch();
    clearWorkSpace();
    while (1) 
    {
        switch (getch()) 
        {


        case 75:x--; break;//left
        case 80:y++; break;//down
        case 72:y--; break;//up
        case 77:x++; break;//right
        case 'c':clearWorkSpace(); break;
        case 27: 
        {
            clear();
            gotoxy(50, 20);
            color("BRIGHTWHITE");
            printf("Thank You");
            gotoxy(0, 40);
            color("WHITE");
            exit(0);
        }break;

        case 'a':color_code = 0; break;
        case 'b':color_code = 1; break;
        case 'd':color_code = 2; break;
        case 'e':color_code = 3; break;
        case 'f':color_code = 4; break;
        case 'g':color_code = 5; break;
        case 'h':color_code = 6; break;
        case 'i':color_code = 7; break;
        case 'j':color_code = 8; break;
        case 'k':color_code = 9; break;
        case 'l':color_code = 12; break;
        case 'm':color_code = 14; break;
            //values
        case '1': ch = '*'; break;
        case '2': ch = 222; break;
        case '3': ch = 205; break;
        case '4': ch = 186; break;
        case '5': ch = 201; break;
        case '6': ch = 187; break;
        case '7': ch = 188; break;
        case '8': ch = 200; break;
        case '9': ch = 250; break;
        }
        if (x < 2)
            x = 119;
        else if (x > 119)
            x = 2;
        else if (y < 2)
            y = 41;
        else if (y > 41)
            y = 2;
        SetConsoleTextAttribute(handle, color_code);
        gotoxy(x, y);
        printf("%c", ch);
    }
    freeColor();
    gotoxy(0, 44);
    return 0;
}

void boarder() 
{
    int i;
    for (i = 1; i < 44; i++) 
    {
        gotoxy(1, i);
        printf("%c", 222);
        gotoxy(100, i);
        printf("%c", 222);
    }

    for (i = 1; i < 60; i++) 
    {
        gotoxy(i, 1);
        printf("%c", 222);
        gotoxy(i, 42);
        printf("%c", 222);
    }

    for (i = 1; i < 42; i++) 
    {
        gotoxy(120, i);
        printf("%c", 222);
    }
    printControls();
}

void clearWorkSpace() 
{
    for (int i = 2; i < 42; i++) 
    {
        for (int j = 2; j < 120; j++) 
        {
            gotoxy(j, i);
            printf(" ");
        }
    }
    x = 30; y = 10;
    gotoxy(x, y);
    printf("%c", 222);
}

void printControls() 
{
    gotoxy(140, 3);
    printf("\nOPTIONS");
    gotoxy(123, 5);
    printf("\nDraw Right = >\n");
    gotoxy(123, 7);
    printf("Draw Left  = <\n");
    gotoxy(123, 9);
    printf("Draw Up    = ^\n");
    gotoxy(123, 11);
    printf("Draw Down  = v\n");
    gotoxy(147, 5);
    printf("clear screen = c\n");
    gotoxy(147, 7);
    printf("start = s\n");
    gotoxy(147, 9);
    printf("");
    gotoxy(147, 11);
    printf("Exit = Esc\n");
    for (int i = 121; i < 150; i++) 
    {
        gotoxy(i, 14);
        printf("%c", 222);
    }
    gotoxy(140, 16);
    printf("\nCUSTOMISE\n");
    gotoxy(123, 18);
    printf("a  =  Black\n");
    gotoxy(123, 20);
    printf("b  =  Blue\n");
    gotoxy(123, 22);
    printf("d  =  Green\n");
    gotoxy(123, 24);
    printf("e  =  Aqua Blue\n");
    gotoxy(123, 26);
    printf("f  =  Red\n");
    gotoxy(123, 28);
    printf("g  =  Purple\n");
    gotoxy(123, 30);
    printf("h  =  Yellow\n");
    gotoxy(123, 32);
    printf("i  =  White\n");
    gotoxy(123, 34);
    printf("j  =  Grey\n");
    gotoxy(123, 36);
    printf("k  =  Light Blue\n");
    gotoxy(123, 38);
    printf("l  =  Light Red\n");
    gotoxy(123, 40);
    printf("m  =  Light Yellow\n");
    for (int i = 1; i < 44; i++)
    {
        gotoxy(100, i);
        printf("%c", 222);
    }
}
