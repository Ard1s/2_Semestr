#include <stdio.h>
#include "func.h"

int NumberOfOptions(int number, unsigned int count, int enumeration, int null)
{
	if (null >= number)
	{
		--number;
		return count;
	}
	if (null <= number)
	{
		switch (enumeration)
		{
		case 1:
			count = NumberOfOptions(number, count + 1, 6, null + 1);
			count = NumberOfOptions(number, count + 1, 8, null + 1);
			break;
		case 2:
			count = NumberOfOptions(number, count + 1, 9, null + 1);
			count = NumberOfOptions(number, count + 1, 7, null + 1);
			break;
		case 3:
			count = NumberOfOptions(number, count + 1, 4, null + 1);
			count = NumberOfOptions(number, count + 1, 8, null + 1);
			break;
		case 4:
			count = NumberOfOptions(number, count + 1, 3, null + 1);
			count = NumberOfOptions(number, count + 1, 9, null + 1);
			count = NumberOfOptions(number, count + 1, 0, null + 1);
			break;
		case 5:
			return count;
			break;
		case 6:
			count = NumberOfOptions(number, count + 1, 1, null + 1);
			count = NumberOfOptions(number, count + 1, 7, null + 1);
			count = NumberOfOptions(number, count + 1, 0, null + 1);
			break;
		case 7:
			count = NumberOfOptions(number, count + 1, 2, null + 1);
			count = NumberOfOptions(number, count + 1, 6, null + 1);
			break;
		case 8:
			if (count == 0) 
			{ 
				return 0; 
			}
			else
			{
				count = NumberOfOptions(number, count + 1, 1, null + 1);
				count = NumberOfOptions(number, count + 1, 3, null + 1);
			}
			break;
		case 9:
			count = NumberOfOptions(number, count + 1, 2, null + 1);
			count = NumberOfOptions(number, count + 1, 4, null + 1);
		case 0:
			if (count == 0) 
			{ 
				return 0; 
			}
			else
			{
				count = NumberOfOptions(number, count + 1, 4, null + 1);
				count = NumberOfOptions(number, count + 1, 6, null + 1);
			}
			break;

		default:
			printf("Неправильный ввод.\n");
		}
	}
	else
	{
		return count;
	}
	return count;
}
