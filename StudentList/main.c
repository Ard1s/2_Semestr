#define _CRT_SECURE_NO_WARNINGS

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <time.h>

#include <windows.h>

#include "list.h"




int main() 
{
	if (!SetConsoleCP(1251)) 
	{
		printf_s("SetConsoleCP failed.\n");
		return 1;
	};
	if (!SetConsoleOutputCP(1251)) 
	{
		printf_s("SetConsoleOutputCP failed.\n");
		return 2;
	}

	srand((unsigned int)time(NULL));

	printf("Вас приветствует межгалактическая база данных студентов.\n");
	printf("adds === добавить студента.\n");
	printf("addsr === добавить случайного студента.\n");
	printf("ri === удалить студента по номеру.\n");
	printf("rln === удалить студента по фамилии.\n");
	printf("rnp === удалить неуспевающих студентов (ср. оценка < 4).\n");
	printf("p === вывести весь список студентов.\n");
	printf("ldt === загрузить список из текстового файла.\n");
	printf("ldb === загрузить список из бинарного файла.\n");
	printf("dt === выгрузить список в текстовый файл.\n");
	printf("db === выгрузить список в бинарный файл.\n");
	printf("pp === вывести успевающих студентов.\n");
	printf("pg === вывести студентов группы.\n");
	printf("piv === вывести студентов c фамилией, начинающейся на \"Ив\".\n");
	printf("p99 === вывести студентов с телефоном, заканчивающимся на 99.\n");
	printf("q === выйти.\n");
	fflush(stdout);

	Student_list* student_list = list_new();
	while (true) 
	{
		printf("> ");
		fflush(stdout);

		char command[5 + 1] = { 0 };
		if (scanf("%5s", command) != 1) 
		{
			printf("Ошибка при чтении команды.\n");
			continue;
		}

		if (strcmp(command, "adds") == 0) 
		{
			student_add(student_list);
		}
		else if (strcmp(command, "addsr") == 0) 
		{
			student_add_random(student_list);
		}
		else if (strcmp(command, "ri") == 0) 
		{
			list_delete_by_index(student_list);
		}
		else if (strcmp(command, "rln") == 0) 
		{
			list_delete_by_last_name(student_list);
		}
		else if (strcmp(command, "rnp") == 0) 
		{
			list_delete_non_performant(student_list);
		}
		else if (strcmp(command, "p") == 0) 
		{
			list_print(student_list);
		}
		else if (strcmp(command, "ldt") == 0) 
		{
			list_load_text(&student_list);
		}
		else if (strcmp(command, "ldb") == 0) 
		{
			list_load_binary(&student_list);
		}
		else if (strcmp(command, "dt") == 0) 
		{
			list_dump_text(student_list);
		}
		else if (strcmp(command, "db") == 0) 
		{
			list_dump_binary(student_list);
		}
		else if (strcmp(command, "pp") == 0) 
		{
			list_print_performant(student_list);
		}
		else if (strcmp(command, "pp") == 0) 
		{
			list_print_groupmates(student_list);
		}
		else if (strcmp(command, "piv") == 0) 
		{
			list_print_IV(student_list);
		}
		else if (strcmp(command, "p99") == 0) 
		{
			list_print_pnumber_99(student_list);
		}
		else if (strcmp(command, "q") == 0) 
		{
			break;
		}
		else 
		{
			printf("Неподдерживаемая команда.\n");
			fflush(stdout);
		}
	}

	student_list = list_delete(student_list);

	return 0;
}