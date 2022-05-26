#define _CRT_SECURE_NO_WARNINGS
#include <ctype.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"

static const uint64_t NUMBER_BASE = 1000 * 1000 * 1000;
static const uint64_t NUMBER_BASE_LOG_10 = 9;
#define NUMBER_BASE_LOG_10_STR "9"
#define MAX_NUM_LEN 100000
#define MAX_NUM_LEN_STR "100000"


int main(int argc, char** argv) 
{
	char* first = NULL;
	char* second = NULL;

	bool free_strings = false;

	if (argc == 3 && strcmp(argv[1], "-f") != 0) 
	{
		first = argv[1];
		second = argv[2];
	}
	else if (argc == 3 && strcmp(argv[1], "-f") == 0) 
	{
		const char* file_name = argv[2];

		FILE* file = fopen(file_name, "r");
		if (file == NULL) 
		{
			fprintf(stderr, "Failed to open file \"%s\".\n", file_name);
			return 1;
		}

		if (!read_numbers(&first, &second, file, file)) 
		{
			fclose(file);
			return 2;
		}
		free_strings = true;

		fclose(file);
	}
	else if (argc == 4 && strcmp(argv[1], "-f") == 0) 
	{
		const char* first_file_name = argv[2];
		const char* second_file_name = argv[3];

		FILE* first_file = fopen(first_file_name, "r");
		if (first_file == NULL) 
		{
			fprintf(stderr, "Failed to open file \"%s\".\n", first_file_name);
			return 1;
		}

		FILE* second_file = fopen(second_file_name, "r");
		if (second_file == NULL) 
		{
			fprintf(stderr, "Failed to open file \"%s\".\n", second_file_name);
			fclose(first_file);
			return 2;
		}

		if (!read_numbers(&first, &second, first_file, second_file)) 
		{
			fclose(first_file);
			fclose(second_file);
			return 3;
		}
		free_strings = true;

		fclose(first_file);
		fclose(second_file);
	}
	else 
	{
		if (!read_numbers(&first, &second, stdin, stdin)) 
		{
			return 3;
		}
		free_strings = true;
	}

	struct number* first_num = number_new(first);
	if (first_num == NULL) 
	{
		return 4;
	}

	struct number* second_num = number_new(second);
	if (second_num == NULL) 
	{
		return 5;
	}

	struct number* add = number_add(first_num, second_num);
	if (add == NULL) 
	{
		return 6;
	}
	char* add_str = number_to_str(add);
	printf("%s + %s = %s.\n", first, second, add_str);
	free(add_str);
	add = number_delete(add);

	struct number* sub = number_sub(first_num, second_num);
	if (sub == NULL) 
	{
		return 7;
	}
	char* sub_str = number_to_str(sub);
	printf("%s - %s = %s.\n", first, second, sub_str);
	free(sub_str);
	sub = number_delete(sub);

	struct number* mul = number_mul(first_num, second_num);
	if (mul == NULL) 
	{
		return 8;
	}
	char* mul_str = number_to_str(mul);
	printf("%s * %s = %s.\n", first, second, mul_str);
	free(mul_str);
	mul = number_delete(mul);

	struct number* div = number_div(first_num, second_num);
	if (div == NULL) 
	{
		return 9;
	}
	char* div_str = number_to_str(div);
	printf("%s / %s = %s.\n", first, second, div_str);
	free(div_str);
	div = number_delete(div);

	first_num = number_delete(first_num);
	second_num = number_delete(second_num);

	if (free_strings) 
	{
		free(first);
		free(second);
	}

	return 0;
}

static bool read_numbers(char** first, char** second, FILE* first_file, FILE* second_file)
{
	*first = calloc(MAX_NUM_LEN + 1, sizeof(char));
	if (*first == NULL)
	{
		return false;
	}

	*second = calloc(MAX_NUM_LEN + 1, sizeof(char));
	if (*second == NULL)
	{
		free(first);
		return false;
	}

	fscanf(first_file, "%" MAX_NUM_LEN_STR "s", *first);
	fscanf(second_file, "%" MAX_NUM_LEN_STR "s", *second);

	if (ferror(first_file) || ferror(second_file))
	{
		return false;
	}

	return true;
}