#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <time.h>

#include <windows.h>

#include "name.h"

#define MAX_STR_LEN 31
#define MAX_NUM_OF_MARKS 10

#define MAX_STR_LEN_FMT "256"


typedef struct student 
{
	struct student* next;

	char first_name[MAX_STR_LEN + 1];
	char last_name[MAX_STR_LEN + 1];
	uint16_t age;

	char group[MAX_STR_LEN + 1];
	char phone_number[MAX_STR_LEN + 1];

	uint8_t marks[MAX_NUM_OF_MARKS];
	uint32_t num_marks;
}Student;

typedef struct student_list 
{
	struct student* head;
	struct student* tail;
}Student_list;


Student_list* list_new() 
{
	Student_list* list = calloc(1, sizeof(Student_list));
	if (list == NULL)
		return NULL;

	return list;
}

Student_list* list_delete(Student_list* list) 
{
	if (list == NULL) 
		return NULL;

	for (Student* student = list->head; student != NULL; student = list->head) 
	{
		list->head = student->next;
		free(student);
	}
	free(list);

	return NULL;
}

bool list_check_empty(Student_list* list)
{
	return list->head == NULL;
}

// Вставляет в конец списка.
void list_insert(Student_list* list, Student* student) 
{
	if (list->head == NULL) 
		list->head = student;

	if (list->tail != NULL) 
		list->tail->next = student;
	list->tail = student;
}

void list_delete_student(Student_list* list, Student* prev_student, Student* student) 
{
	if (list->head == list->tail) 
		list->tail = NULL;

	if (prev_student != NULL) 
		prev_student->next = student->next;
	else 
		list->head = student->next;

	free(student);
}

void student_add(Student_list* list) 
{
	Student* student = calloc(1, sizeof(Student));
	if (student == NULL) 
	{
		printf("Не удалось выделить память!\n");
		fflush(stdout);
		return;
	}

	printf("Введите имя: ");
	fflush(stdout);
	if (scanf(" %" MAX_STR_LEN_FMT "[^\",)\n]", student->first_name) != 1) 
	{
		printf("Ошибка при чтении.\n");
		free(student);
		return;
	}

	printf("Введите фамилию: ");
	fflush(stdout);
	if (scanf(" %" MAX_STR_LEN_FMT "[^\",)\n]", student->last_name) != 1) 
	{
		printf("Ошибка при чтении.\n");
		free(student);
		return;
	}

	printf("Введите возраст: ");
	fflush(stdout);
	if (scanf("%" SCNu16, &student->age) != 1) 
	{
		printf("Ошибка при чтении.\n");
		free(student);
		return;
	}

	printf("Введите группу: ");
	fflush(stdout);
	if (scanf(" %" MAX_STR_LEN_FMT "[^\",)\n]", student->group) != 1) 
	{
		printf("Ошибка при чтении.\n");
		free(student);
		return;
	}

	printf("Введите номер телефона: ");
	fflush(stdout);
	if (scanf(" %" MAX_STR_LEN_FMT "[^\",)\n]", student->phone_number) != 1) 
	{
		printf("Ошибка при чтении.\n");
		free(student);
		return;
	}

	printf("Введите оценки, когда закончите, напишите -1:");
	fflush(stdout);
	while (true) 
	{
		int8_t value = 0;
		if (scanf("%" SCNd8, &value) != 1) 
		{
			printf("Ошибка при чтении.\n");
			break;
		}
		if (value < 0)
			break;
		else 
		{
			student->marks[student->num_marks] = (uint8_t)value;
			student->num_marks += 1;
		}
	}

	list_insert(list, student);
	printf("Студент добавлен успешно.\n");
}

char const* pick_random_str(char const** array, size_t size) 
{
	return array[rand() % size];
}

void student_add_random(Student_list* list) 
{
	Student* student = calloc(1, sizeof(Student));
	if (student == NULL) 
	{
		printf("Не удалось выделить память!\n");
		return;
	}

	switch (rand() % 2) 
	{
	case 0: 
	{
		strncpy(student->first_name, pick_random_str(WOMAN_NAMES, sizeof(WOMAN_NAMES) / sizeof(*WOMAN_NAMES)), MAX_STR_LEN + 1);
		if (student->first_name[MAX_STR_LEN] != '\0') 
		{
			printf("Не удалось выбрать имя.\n");
			free(student);
			return;
		}

		strncpy(student->last_name, pick_random_str(LAST_NAMES, sizeof(LAST_NAMES) / sizeof(*LAST_NAMES)), MAX_STR_LEN + 1);
		if (student->last_name[MAX_STR_LEN - 1] != '\0') 
		{
			printf("Не удалось выбрать фамилию.\n");
			free(student);
			return;
		}

		strcat(student->last_name, "а");

		break;
	}

	case 1: 
	{
		strncpy(student->first_name, pick_random_str(MAN_NAMES, sizeof(MAN_NAMES) / sizeof(*MAN_NAMES)), MAX_STR_LEN + 1);
		if (student->first_name[MAX_STR_LEN] != '\0') 
		{
			printf("Не удалось выбрать имя.\n");
			free(student);
			return;
		}

		strncpy(student->last_name, pick_random_str(LAST_NAMES, sizeof(LAST_NAMES) / sizeof(*LAST_NAMES)), MAX_STR_LEN + 1);
		if (student->last_name[MAX_STR_LEN] != '\0') 
		{
			printf("Не удалось выбрать фамилию.\n");
			free(student);
			return;
		}

		break;
	}
	};

	student->age = 17 + (rand() % 20);
	strcpy(student->group, "М");

	switch (rand() % 2) 
	{
	case 0: 
	{
		strcat(student->group, "к");
		break;
	}

	case 1: 
	{
		strcat(student->group, "п");
		break;
	}
	}

	strcat(student->group, "-");

	char course[2] = { 0 };
	course[0] = '0' + rand() % 4;

	strcat(student->group, course);

	strcat(student->group, "0");

	char number[2] = { 0 };
	number[0] = '0' + rand() % 4;

	strcat(student->group, number);

	strcat(student->phone_number, "+79");

	for (size_t i = 3; i < 12; ++i) 
	{
		char digit[2] = { 0 };
		digit[0] = '0' + rand() % 9;
		strcat(student->phone_number, digit);
	}

	student->num_marks = rand() % MAX_NUM_OF_MARKS;
	for (size_t i = 0; i < student->num_marks; ++i) 
		student->marks[i] = 3 + rand() % 3;

	list_insert(list, student);
}

bool student_dump_text(FILE* file, Student* student) 
{
	int result = fprintf(file, "Студент \"%s\" \"%s\" (возраст: %" PRIu16 ", группа: %s, оценки: ", student->first_name, student->last_name, student->age, student->group);
	if (result < 0) 
		return false;
	for (size_t i = 0; i < student->num_marks; ++i) 
	{
		result = fprintf(file, "%" PRIu8 ",", student->marks[i]);
		if (result < 0) 
			return false;
	}
	result = fprintf(file, ", номер телефона: %s).\n", student->phone_number);
	if (result < 0) 
		return false;

	return true;
}

bool student_dump_binary(FILE* file, Student* student) 
{
	return fwrite(student, sizeof(Student), 1, file) == 1;
}

bool student_load_text(FILE* file, Student* student) 
{
	int result = fscanf(file, "Студент \"%" MAX_STR_LEN_FMT "[^\"]\" \"%" MAX_STR_LEN_FMT "[^\"]\" (возраст: %" SCNu16 ", группа: %" MAX_STR_LEN_FMT "[^,], оценки: ", student->first_name, student->last_name, &student->age, student->group);
	if (result != 4)
		return false;

	student->num_marks = 0;
	for (size_t i = 0; i < MAX_NUM_OF_MARKS; ++i) 
	{
		uint16_t grade = 0;
		result = fscanf(file, "%" SCNu16 ",", &grade);
		if (result != 1)
			break;
		student->marks[student->num_marks] = (uint8_t)grade;
		student->num_marks += 1;
	}

	result = fscanf(file, ", номер телефона: %" MAX_STR_LEN_FMT "[^)]).\n", student->phone_number);
	if (result != 1) 
		return false;

	return true;
}

bool student_load_binary(FILE* file, Student* student) 
{
	return fread(student, sizeof(Student), 1, file) == 1;
}

bool student_print(Student* student) 
{
	return student_dump_text(stdout, student);
}

void list_print(Student_list* list) 
{
	for (Student* student = list->head; student != NULL; student = student->next) 
	{
		if (!student_print(student)) 
		{
			printf("Ошибка при выводе.\n");
			break;
		}
	}
	fflush(stdout);
}

void list_load_text(Student_list** list) 
{
	if (!list_check_empty(*list)) 
	{
		printf("Список не пуст. Он будет удалён. Продолжить? Да/Нет.");
		fflush(stdout);

		char answer = 0;
		scanf_s(1," %c", &answer);
		if (answer != 'Да') 
			return;
	}

	char file_name[MAX_STR_LEN + 1] = { 0 };
	printf("Введите имя файла: ");
	fflush(stdout);
	if (scanf("%" MAX_STR_LEN_FMT "s", file_name) != 1) 
	{
		printf("Не удалось прочитать название файла.\n");
		fflush(stdout);
		return;
	}

	FILE* file = fopen(file_name, "r");
	if (file == NULL) 
	{
		printf("Не удалось открыть файл.\n");
		fflush(stdout);
		return;
	}

	*list = list_delete(*list);
	*list = list_new();

	while (true) 
	{
		int byte = getc(file);
		if (feof(file))
			break;
		ungetc(byte, file);

		Student* student = calloc(1, sizeof(Student));

		if (!student_load_text(file, student)) 
		{
			printf("Ошибка при чтении файла.\n");
			free(student);
			printf("Список был прочитан не полностью.\n");
			break;
		}

		list_insert(*list, student);
	}

	fclose(file);
}

void list_load_binary(Student_list** list) 
{
	if (!list_check_empty(*list)) 
	{
		printf("Список не пуст. Он будет удалён. Продолжить? Да/Нет.");
		fflush(stdout);

		char answer = 0;
		scanf_s(1, " %c", &answer);
		if (answer != 'Да') 
		{
			return;
		}
	}

	char file_name[MAX_STR_LEN + 1] = { 0 };
	printf("Введите имя файла: ");
	fflush(stdout);
	if (scanf("%" MAX_STR_LEN_FMT "s", file_name) != 1) 
	{
		printf("Не удалось прочитать название файла.\n");
		fflush(stdout);
		return;
	}

	FILE* file = fopen(file_name, "rb");
	if (file == NULL) 
	{
		printf("Не удалось открыть файл.\n");
		fflush(stdout);
		return;
	}

	*list = list_delete(*list);
	*list = list_new();

	while (true) 
	{
		int byte = getc(file);
		if (feof(file)) 
			break;
		ungetc(byte, file);

		Student* student = calloc(1, sizeof(Student));

		if (!student_load_binary(file, student)) 
		{
			printf("Ошибка при чтении файла.\n");
			free(student);
			printf("Список был прочитан не полностью.\n");
			fflush(stdout);
			break;
		}

		list_insert(*list, student);
	}

	fclose(file);
}

void list_dump_text(Student_list* list) 
{
	char file_name[MAX_STR_LEN + 1] = { 0 };
	printf("Введите имя файла: ");
	fflush(stdout);
	if (scanf("%" MAX_STR_LEN_FMT "s", file_name) != 1) 
	{
		printf("Не удалось прочитать название файла.\n");
		fflush(stdout);
		return;
	}

	FILE* file = fopen(file_name, "w");
	if (file == NULL) {
		printf("Не удалось открыть файл.\n");
		fflush(stdout);
		return;
	}

	for (Student* student = list->head; student != NULL; student = student->next) 
	{
		if (!student_dump_text(file, student)) 
		{
			printf("Ошибка при записи в файл. Выходной файл может быть повреждён.\n");
			fflush(stdout);
			break;
		}
	}

	fclose(file);
}

void list_dump_binary(Student_list* list) 
{
	char file_name[MAX_STR_LEN + 1] = { 0 };
	printf("Введите имя файла: ");
	fflush(stdout);
	if (scanf("%" MAX_STR_LEN_FMT "s", file_name) != 1) 
	{
		printf("Не удалось прочитать название файла.\n");
		fflush(stdout);
		return;
	}

	FILE* file = fopen(file_name, "wb");
	if (file == NULL) 
	{
		printf("Не удалось открыть файл.\n");
		fflush(stdout);
		return;
	}

	for (Student* student = list->head; student != NULL; student = student->next) 
	{
		if (!student_dump_binary(file, student)) 
		{
			printf("Ошибка при записи в файл. Выходной файл может быть повреждён.\n");
			fflush(stdout);
			break;
		}
	}

	fclose(file);
}

void list_print_performant(Student_list* list) 
{
	for (Student* student = list->head; student != NULL; student = student->next) 
	{
		if (student->num_marks == 0) 
			continue;
		unsigned long long avg_mark = 0;
		for (size_t i = 0; i < student->num_marks; ++i) 
			avg_mark += student->marks[i];
		// Средняя оценка с округлением вверх.
		avg_mark = (avg_mark + (student->num_marks + 1) / 2) / student->num_marks;
		if (avg_mark >= 4) 
		{
			if (!student_print(student)) 
			{
				printf("Ошибка при выводе.\n");
				break;
			}
		}
	}
	fflush(stdout);
}

void list_print_groupmates(Student_list* list) 
{
	char group[MAX_STR_LEN + 1] = { 0 };
	if (scanf("%" MAX_STR_LEN_FMT "s", group) != 1) 
	{
		printf("Не удалось прочитать название группы.\n");
		fflush(stdout);
		return;
	}

	for (Student* student = list->head; student != NULL; student = student->next) 
	{
		if (strcmp(student->group, group) == 0) 
		{
			if (!student_print(student)) {
				printf("Ошибка при выводе.\n");
				break;
			}
		}
	}
	fflush(stdout);
}

void list_print_IV(Student_list* list) 
{
	for (Student* student = list->head; student != NULL; student = student->next) 
	{
		if (strncmp(student->last_name, "Ив", 2) == 0) {
			if (!student_print(student)) 
			{
				printf("Ошибка при выводе.\n");
				break;
			}
		}
	}
	fflush(stdout);
}

void list_print_pnumber_99(Student_list* list) 
{
	for (Student* student = list->head; student != NULL; student = student->next) 
	{
		if (strcmp(student->phone_number + strlen(student->phone_number) - 2, "99") == 0) 
		{
			if (!student_print(student)) 
			{
				printf("Ошибка при выводе.\n");
				break;
			}
		}
	}
	fflush(stdout);
}

void list_delete_by_index(Student_list* list) 
{
	printf("Введите индекс: ");
	fflush(stdout);

	size_t index = 0;
	if (scanf("%zu", &index) != 1) 
	{
		printf("Не удалось прочитать индекс.\n");
		fflush(stdout);
		return;
	}

	Student* prev_student = NULL;
	Student* student = list->head;
	for (size_t i = 0; i < index; ++i) 
	{
		if (student == NULL) 
			break;
		prev_student = student;
		student = student->next;
	}

	if (student == NULL) 
	{
		printf("Студент не найден.\n");
		fflush(stdout);
		return;
	}

	list_delete_student(list, prev_student, student);
}

void list_delete_by_last_name(Student_list* list) 
{
	printf("Введите фамилию: ");
	fflush(stdout);

	char last_name[MAX_STR_LEN + 1] = { 0 };

	if (scanf(" %" MAX_STR_LEN_FMT "[^\n]", last_name) != 1) 
	{
		printf("Не удалось прочитать фамилию.\n");
		fflush(stdout);
		return;
	}

	Student* prev_student = NULL;
	Student* student = NULL;
	for (; student != NULL; prev_student = student, student = student->next) 
	{
		if (student == NULL) 
		{
			break;
		}
		if (strcmp(student->last_name, last_name) == 0) 
		{
			break;
		}
		prev_student = student;
		student = student->next;
	}

	if (student == NULL) 
	{
		printf("Студент не найден.\n");
		fflush(stdout);
		return;
	}

	list_delete_student(list, prev_student, student);
}

void list_delete_non_performant(Student_list* list) 
{
	Student* prev_student = NULL;
	for (Student* student = list->head; student != NULL; prev_student = student, student = student->next) 
	{
		if (student->num_marks == 0) 
			continue;
		unsigned long long avg_mark = 0;
		for (size_t i = 0; i < student->num_marks; ++i) 
			avg_mark += student->marks[i];
		// Средняя оценка с округлением вверх.
		avg_mark = (avg_mark + (student->num_marks + 1) / 2) / student->num_marks;
		if (avg_mark < 4) {
			list_delete_student(list, prev_student, student);
		}
	}
}