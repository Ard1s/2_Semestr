#include <stdio.h>
#include <locale.h>
#include "func.h"


int main() 
{
	setlocale(LC_ALL, "Rus");
	unsigned int number = 0;
	unsigned int counter = 0;
	unsigned int Options = 0;
	printf_s("������� ����� �� 1 �� 9. 0 � 8 �������� ������\n");
	scanf_s("%d", &number);
	for (int i = 0; i <= 9; ++i) 
	{
		counter = 0;
		counter = NumberOfOptions(number, counter, i, 0);
		Options += counter;
	}
	printf_s("%d\n", Options);
	system("pause");
}