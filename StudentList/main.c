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

	printf("��� ������������ ���������������� ���� ������ ���������.\n");
	printf("adds === �������� ��������.\n");
	printf("addsr === �������� ���������� ��������.\n");
	printf("ri === ������� �������� �� ������.\n");
	printf("rln === ������� �������� �� �������.\n");
	printf("rnp === ������� ������������ ��������� (��. ������ < 4).\n");
	printf("p === ������� ���� ������ ���������.\n");
	printf("ldt === ��������� ������ �� ���������� �����.\n");
	printf("ldb === ��������� ������ �� ��������� �����.\n");
	printf("dt === ��������� ������ � ��������� ����.\n");
	printf("db === ��������� ������ � �������� ����.\n");
	printf("pp === ������� ���������� ���������.\n");
	printf("pg === ������� ��������� ������.\n");
	printf("piv === ������� ��������� c ��������, ������������ �� \"��\".\n");
	printf("p99 === ������� ��������� � ���������, ��������������� �� 99.\n");
	printf("q === �����.\n");
	fflush(stdout);

	Student_list* student_list = list_new();
	while (true) 
	{
		printf("> ");
		fflush(stdout);

		char command[5 + 1] = { 0 };
		if (scanf("%5s", command) != 1) 
		{
			printf("������ ��� ������ �������.\n");
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
			printf("���������������� �������.\n");
			fflush(stdout);
		}
	}

	student_list = list_delete(student_list);

	return 0;
}