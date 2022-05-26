#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <Windows.h>


#include "sum.h"

int main()
{
	printf("%d\n", sum(4, 1, 2, 3, 4));
	printf("%f\n", summ(4, 1.3, 2.5, 3, 4));
	printf("%d\n", sum_via_stdargMACROSES(4, 1, 2, 3, 4));

	// это нужно реализовать вам и протестировать в x86 и x64
	printf("%lf\n", sumDouble(4, 1.1, 2.2, 3.0, 0.1));
	printf("%lf\n", sum_double_via_stdargMACROSES(4, 1.1, 2.2, 3.0, 0.1));

	char* str1 = concat("one ", "two ", "three ", "four", "\0");
	printf("%s\n", str1);
	free(str1);
	str1 = concat("Happy ", "new ", "year!", "\0");
	printf("%s\n", str1);
	free(str1);
	str1 = concat("Hello ", "world!", "\0");
	printf("%s\n", str1);
	free(str1);

	system("pause");
	return 0;
}