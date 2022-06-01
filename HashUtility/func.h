#pragma once
#include <stdint.h>

void slstore(struct htype* i, struct htype* start);
void store(char* cell_name, int v);
int find(char* cell_name);
void print_bytes(void* p, size_t length);
void print_hash(uint8_t* p);

