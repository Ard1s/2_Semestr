#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define SIZE 2
int matrix[SIZE][SIZE]; 
int vertexes[SIZE]; 
long minimum[SIZE]; 
int save;
int begin_index = 0;
int min;
int minindex;

void matrix_connection()
{
    for (int i = 0; i < SIZE; i++)
    {
        matrix[i][i] = 0;
        for (int j = 0; j < SIZE; j++) 
        {
            printf("Enter the value in the matrix with the index  %d - %d: ", i + 1, j + 1);
            scanf("%d", &save);
            matrix[i][j] = save;
        }
    }
}

void outPut_matrix()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
            printf("%5d ", matrix[i][j]);
        printf("\n");
    }
}

void waveAlgorithm()
{

    for (int i = 0; i < SIZE; i++)
    {
        minimum[i] = 10000;
        vertexes[i] = 1;

    }
    minimum[begin_index] = 0;

    do {
        minindex = 10000;
        min = 10000;
        for (int i = 0; i < SIZE; i++)
        {
            if ((vertexes[i] == 1) && (minimum[i] < min))
            {
                min = minimum[i];
                minindex = i;
            }
        }

        if (minindex != 10000)
        {
            for (int i = 0; i < SIZE; i++)
            {
                if (matrix[minindex][i] > 0)
                {
                    save = min + matrix[minindex][i];
                    if (save < minimum[i])
                    {
                        minimum[i] = save;
                    }
                }
            }
            vertexes[minindex] = 0;
        }
    } while (minindex < 10000);

}

void v_p()
{
    int ver[SIZE]; 
    int end = 5; 
    ver[0] = end + 1; 
    int k = 1; 
    int weight = minimum[end]; 

    while (end != begin_index) 
    {
        for (int i = 0; i < SIZE; i++)
            if (matrix[i][end] != 0)
            {
                int temp = weight - matrix[i][end]; 
                if (temp == minimum[i])
                {
                    weight = temp;
                    end = i; 
                    ver[k] = i + 1; 
                    k++;
                }
            }
    }

    printf("\n\nThe shortest path: \n");
    for (int i = 0; i < SIZE; i++)
        printf("%5d ", minimum[i]);

    printf("\nOutput of the shortest path:\n");
    for (int i = k - 1; i >= 0; i--)
        printf("%3d ", ver[i]);
}
int main()
{
    matrix_connection();
    outPut_matrix();
    waveAlgorithm();
    v_p();
    getchar();
    getchar();
    return 0;
}