#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "func.h"
#include <conio.h>

#define MAX_LENGTH 10
#define NUMBER "314"


void permutation(char string[], int k)
{
    static int perm[MAX_LENGTH] = { 0 };
    static char Res[MAX_LENGTH];
    int i;
    if (string[k] == '\0')
    {
        Res[k] = '\0';
        printf("%s\n", Res);
    }
    else
    {
        for (int i = 0; string[i] != '\0'; i++)
        {
            if (perm[i] == 0)
            {
                Res[k] = string[i];
                perm[i] = 1;
                permutation(string, k + 1);
                perm[i] = 0;
            }
        }
    }
}


int main()
{
    char orig[] = NUMBER;
    printf("string is \" % s\"\n", orig);
    printf("Permutations are : \n");
    permutation(orig, 0);
    return 0;
}
