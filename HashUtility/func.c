#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <stdint.h>
#include "raylib.h"
#include "func.h"

#define MAX 260 

struct htype
{
	int index;
	int val;
	struct htype* next;
}primary[MAX];

void slstore(struct htype* i, struct htype* start)
{
	struct htype* old, * p;
	old = start;
	while (start)
	{
		old = start; start = start->next;
	}
	old->next = i;
	i->next = NULL;
}

void store(char* cell_name, int v)
{
	int h, loc; struct htype* p;
	loc = *cell_name - 'A';
	loc += (atoi(&cell_name[1]) - 1) * 26;
	h = loc / 10;
	if (primary[h].index == -1 || primary[h].index == loc)
	{
		primary[h].index = loc; primary[h].val = v; return;
	}
	p = (struct htype*)malloc(sizeof(struct htype));
	if (!p)
	{
		printf("Не хватает памяти\n");
		return;
	}
	p->index = loc;
	p->val = v;
	slstore(p, &primary[h]);
}



int find(char* cell_name)
{
	int h, loc; struct htype* p;
	loc = *cell_name - 'A';
	loc += (atoi(&cell_name[1]) - 1) * 26;
	h = loc / 10;
	if (primary[h].index == loc)
		return(primary[h].val);
	else
	{
		p = primary[h].next;
		while (p)
		{
			if (p->index == loc)
				return p->val;
			p = p->next;
		}
		printf("Ячейки нет в массиве\n");
		return -1;
	}
}

void print_bytes(void* p, size_t length) 
{
	uint8_t* pp = (uint8_t*)p;
	for (unsigned int i = 0; i < length; ++i) 
	{
		if (i && !(i % 16)) 
		{
			printf("\n");
		}
		printf("%02X ", pp[i]);
	}
	printf("\n");
}

void print_hash(uint8_t* p) 
{
	for (unsigned int i = 0; i < 16; ++i) 
	{
		printf("%02x", p[i]);
	}
	printf("\n");
}

bool IsAnyKeyPressed()
{
	bool keyPressed = false;
	int key = GetKeyPressed();

	if ((key >= 32) && (key <= 126)) keyPressed = true;

	return keyPressed;
}