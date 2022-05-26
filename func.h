#pragma once
#include <stdio.h>

struct number;
struct number* number_new(const char* number_string);
struct number* number_delete(struct number* number);
char* number_to_str(struct number* number);
static void number_delete_leading_zeros(struct number* number);
static struct number* number_add_positive(struct number* lhs, struct number* rhs);
struct number* number_add(struct number* lhs, struct number* rhs);
int number_compare(struct number const* lhs, struct number const* rhs);
static struct number* number_sub_positive(struct number* lhs, struct number* rhs);
struct number* number_sub(struct number* lhs, struct number* rhs);
struct number* number_mul(struct number* lhs, struct number* rhs);
struct number* number_div(struct number* nominator, struct number* denominator);
static bool read_numbers(char** first, char** second, FILE* first_file, FILE* second_file);


