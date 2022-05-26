#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>


int sum(int n, ...)
{
	int result = 0;
	int* ptr = &n;
	++ptr;
	while (n > 0)
	{
		result += *ptr;
		++ptr;
		--n;
	}
	return result;
}

double summ(int n, ...)
{
	double result = 0;
	double* ptr = &n + 1;
	for (; n > 0; n--)
		result += *(ptr++);
	return result;
}

int sum_via_stdargMACROSES(int n, ...)
{
	va_list arglist;
	va_start(arglist, n);
	int result = 0, i = 0;
	while (n > 0)
	{
		i = va_arg(arglist, int);
		result += i;
		--n;
	}
	va_end(arglist);
	return result;
}
double sumDouble(double n, ...)
{
	double result = 0;
	double* ptr = &n;
	++ptr;
	while (n > 0)
	{
		result += *ptr;
		++ptr;
		--n;
	}
	return result;
}
double sum_double_via_stdargMACROSES(int n, ...)
{
	va_list arglist;
	va_start(arglist, n);
	double result = 0, i = 0;
	while (n > 0)
	{
		i = va_arg(arglist, double);
		result += i;
		--n;
	}
	va_end(arglist);
	return result;
}

char* concat(char* strsrc, ...)
{
	va_list arglist;
	va_start(arglist, strsrc);

	int mainlen = strlen(strsrc);

	char* tmpstr = NULL;

	do
	{
		tmpstr = va_arg(arglist, char*);
		mainlen += strlen(tmpstr);
	} while (tmpstr[0] != '\0');

	va_end(arglist);
	va_start(arglist, strsrc);

	printf("%d", mainlen);
	return 0;
}


