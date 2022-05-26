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

struct number 
{
	uint64_t* digits;
	bool is_negative;
	size_t num_digits;
};

struct number* number_new(const char* number_string) 
{
	struct number* number = calloc(1, sizeof(struct number));
	if (number == NULL) 
	{
		return NULL;
	}

	if (*number_string == '-') 
	{
		number->is_negative = true;
		++number_string;
	}
	else if (*number_string == '+') 
	{
		number->is_negative = false;
		++number_string;
	}

	while (*number_string == '0') 
	{
		++number_string;
	}

	size_t number_string_len = strlen(number_string);

	if (number_string_len == 0) 
	{
		number->num_digits = 0;
		number->is_negative = false;
		return number;
	}

	number->num_digits = (number_string_len + NUMBER_BASE_LOG_10 - 1) / NUMBER_BASE_LOG_10;
	number->digits = calloc(number->num_digits, sizeof(uint64_t));

	if (number->digits == NULL) 
	{
		free(number);
		return NULL;
	}

	size_t num_in_first_digit = number_string_len % NUMBER_BASE_LOG_10;
	if (num_in_first_digit == 0) 
	{
		num_in_first_digit = NUMBER_BASE_LOG_10;
	}

	{
		uint64_t digit = 0;

		for (size_t j = 0; j < num_in_first_digit; ++j, ++number_string) 
		{
			if (!isdigit(*number_string)) 
			{
				free(number->digits);
				free(number);
				return NULL;
			}
			digit *= 10;
			digit += *number_string - '0';
		}
		number->digits[0] = digit;
	}

	for (size_t i = 1; i < number->num_digits; ++i) 
	{
		uint64_t digit = 0;

		for (size_t j = 0; j < NUMBER_BASE_LOG_10; ++j, ++number_string) 
		{
			if (!isdigit(*number_string)) 
			{
				free(number->digits);
				free(number);
				return NULL;
			}
			digit *= 10;
			digit += *number_string - '0';
		}
		number->digits[i] = digit;
	}

	return number;
}

struct number* number_delete(struct number* number) 
{
	free(number->digits);
	free(number);

	return NULL;
}

char* number_to_str(struct number* number) 
{
	size_t string_len = number->num_digits * NUMBER_BASE_LOG_10;

	char* buffer = calloc(1 + string_len + 1, sizeof(char));
	if (buffer == NULL) 
	{
		return NULL;
	}

	if (number->num_digits == 0) 
	{
		buffer[0] = '0';
		buffer[1] = '\0';
		return buffer;
	}

	char* cur_char = buffer;

	if (number->is_negative) 
	{
		*cur_char = '-';
		++cur_char;
	}

	// Первую цифру нужно положить как есть, чтобы не было ведущих нулей.
	{
		size_t num_digits_10 = snprintf(cur_char, NUMBER_BASE_LOG_10 + 1, "%" PRIu64, number->digits[0]);
		cur_char += num_digits_10;
	}

	for (size_t i = 1; i < number->num_digits; ++i) 
	{
		snprintf(cur_char, NUMBER_BASE_LOG_10 + 1, "%0" NUMBER_BASE_LOG_10_STR PRIu64, number->digits[i]);
		cur_char += NUMBER_BASE_LOG_10;
	}

	return buffer;
}

static void number_delete_leading_zeros(struct number* number) 
{
	size_t num_leading_zeros = 0;
	for (size_t i = 0; i < number->num_digits; ++i) 
	{
		if (number->digits[i] == 0) 
		{
			num_leading_zeros += 1;
		}
		else 
		{
			break;
		}
	}

	for (size_t i = num_leading_zeros; i < number->num_digits; ++i) 
	{
		number->digits[i - num_leading_zeros] = number->digits[i];
	}
	number->num_digits -= num_leading_zeros;
}

static struct number* number_add_positive(struct number* lhs, struct number* rhs) 
{
	struct number* number = calloc(1, sizeof(struct number));
	if (number == NULL) 
	{
		return NULL;
	}

	number->is_negative = false;

	if (rhs->num_digits < lhs->num_digits) 
	{
		struct number* tmp = lhs;
		lhs = rhs;
		rhs = tmp;
	}

	number->num_digits = rhs->num_digits + 1;
	number->digits = calloc(number->num_digits, sizeof(uint64_t));
	if (number->digits == NULL) {
		free(number);
		return NULL;
	}

	size_t cmn_len = lhs->num_digits;

	uint64_t carry = 0;
	for (size_t i = 0; i < cmn_len; ++i) 
	{
		size_t number_pos = number->num_digits - i - 1;
		size_t lhs_pos = lhs->num_digits - i - 1;
		size_t rhs_pos = rhs->num_digits - i - 1;

		number->digits[number_pos] = carry + lhs->digits[lhs_pos] + rhs->digits[rhs_pos];

		carry = number->digits[number_pos] / NUMBER_BASE;
		number->digits[number_pos] %= NUMBER_BASE;
	}

	for (size_t i = cmn_len; i < rhs->num_digits; ++i) 
	{
		size_t number_pos = number->num_digits - i - 1;
		size_t rhs_pos = rhs->num_digits - i - 1;

		number->digits[number_pos] = carry + rhs->digits[rhs_pos];

		carry = number->digits[number_pos] / NUMBER_BASE;
		number->digits[number_pos] %= NUMBER_BASE;
	}
	number->digits[0] = carry;

	number_delete_leading_zeros(number);

	return number;
}

static struct number* number_sub_positive(struct number* lhs, struct number* rhs);
struct number* number_add(struct number* lhs, struct number* rhs) 
{
	if (lhs->is_negative != rhs->is_negative) 
	{
		if (lhs->is_negative) 
		{
			lhs->is_negative = false;
			struct number* result = number_sub_positive(rhs, lhs);
			lhs->is_negative = true;
			return result;
		}
		else 
		{
			rhs->is_negative = false;
			struct number* result = number_sub_positive(lhs, rhs);
			rhs->is_negative = true;
			return result;
		}
	}
	else if (lhs->is_negative) 
	{
		lhs->is_negative = false;
		rhs->is_negative = false;
		struct number* result = number_add_positive(lhs, rhs);
		if (result != NULL) 
		{
			result->is_negative = true;
		}
		lhs->is_negative = true;
		rhs->is_negative = true;
		return result;
	}
	else 
	{
		return number_add_positive(lhs, rhs);
	}
}

int number_compare(struct number const* lhs, struct number const* rhs) 
{
	if (lhs->is_negative != rhs->is_negative) 
	{
		if (lhs->is_negative) 
		{
			return -1;
		}
		else 
		{
			return 1;
		}
	}
	else 
	{
		bool inverse = false;
		if (lhs->is_negative) 
		{
			inverse = true;
		}
		int result = 0;
		if (lhs->num_digits > rhs->num_digits) 
		{
			result = 1;
		}
		else if (lhs->num_digits < rhs->num_digits) 
		{
			result = -1;
		}
		else 
		{
			for (size_t i = 0; i < lhs->num_digits; ++i) 
			{
				if (lhs->digits[i] != rhs->digits[i]) 
				{
					if (lhs->digits[i] > rhs->digits[i]) 
					{
						result = 1;
					}
					else 
					{
						result = -1;
					}
					break;
				}
			}
		}
		if (inverse) 
		{
			result *= -1;
		}
		return result;
	}
}

static struct number* number_sub_positive(struct number* lhs, struct number* rhs) 
{
	int comparison = number_compare(lhs, rhs);

	bool inverse = false;
	if (comparison == 0) 
	{
		struct number* number = calloc(1, sizeof(struct number));
		if (number == NULL) 
		{
			return NULL;
		}
		number->digits = NULL;
		number->num_digits = 0;
		number->is_negative = false;
		return number;
	}
	else if (comparison < 0) 
	{
		inverse = true;

		struct number* tmp = rhs;
		rhs = lhs;
		lhs = tmp;
	}

	struct number* number = calloc(1, sizeof(struct number));
	if (number == NULL) 
	{
		return NULL;
	}

	number->num_digits = lhs->num_digits;
	number->digits = calloc(number->num_digits, sizeof(uint64_t));
	if (number->digits == NULL) 
	{
		free(number);
		return NULL;
	}

	size_t cmn_len = rhs->num_digits;
	int taken = 0;
	for (size_t i = 0; i < cmn_len; ++i) 
	{
		size_t number_pos = number->num_digits - i - 1;
		size_t lhs_pos = lhs->num_digits - i - 1;
		size_t rhs_pos = rhs->num_digits - i - 1;

		int64_t value = (int64_t)lhs->digits[lhs_pos] - taken - (int64_t)rhs->digits[rhs_pos];
		if (value < 0) 
		{
			taken = 1;
			value += NUMBER_BASE;
		}
		else 
		{
			taken = 0;
		}
		number->digits[number_pos] = (uint64_t)value;
	}

	for (size_t i = cmn_len; i < lhs->num_digits; ++i) 
	{
		size_t number_pos = number->num_digits - i - 1;
		size_t lhs_pos = lhs->num_digits - i - 1;

		int64_t value = (int64_t)lhs->digits[lhs_pos] - taken;
		if (value < 0) 
		{
			taken = 1;
			value += NUMBER_BASE;
		}
		else {
			taken = 0;
		}
		number->digits[number_pos] = (uint64_t)value;
	}

	if (inverse) 
	{
		number->is_negative = true;
	}

	number_delete_leading_zeros(number);

	return number;
}

struct number* number_sub(struct number* lhs, struct number* rhs) 
{
	if (lhs->is_negative != rhs->is_negative) 
	{
		if (lhs->is_negative) 
		{
			lhs->is_negative = false;
			struct number* result = number_add_positive(lhs, rhs);
			if (result != NULL) 
			{
				result->is_negative = true;
			}
			lhs->is_negative = true;
			return result;
		}
		else 
		{
			rhs->is_negative = false;
			struct number* result = number_add_positive(lhs, rhs);
			rhs->is_negative = true;
			return result;
		}
	}
	else if (lhs->is_negative) 
	{
		lhs->is_negative = false;
		rhs->is_negative = false;
		struct number* result = number_sub_positive(rhs, lhs);
		lhs->is_negative = true;
		rhs->is_negative = true;
		return result;
	}
	else 
	{
		return number_sub_positive(lhs, rhs);
	}
}

struct number* number_mul(struct number* lhs, struct number* rhs) 
{
	if (lhs->num_digits == 0 || rhs->num_digits == 0) 
	{
		struct number* number = calloc(1, sizeof(struct number));
		number->digits = NULL;
		number->num_digits = 0;
		number->is_negative = false;
		return number;
	}

	bool inverse = false;
	if (lhs->is_negative != rhs->is_negative) 
	{
		inverse = true;
	}

	struct number* number = calloc(1, sizeof(struct number));
	if (number == NULL) 
	{
		return NULL;
	}

	number->num_digits = lhs->num_digits + rhs->num_digits + 1;

	number->digits = calloc(number->num_digits, sizeof(uint64_t));
	if (number->digits == NULL) 
	{
		free(number);
		return NULL;
	}

	for (size_t i = 0; i < lhs->num_digits; ++i) 
	{
		size_t lhs_pos = lhs->num_digits - i - 1;

		uint64_t carry = 0;
		for (size_t j = 0; j < rhs->num_digits; ++j) 
		{
			size_t rhs_pos = rhs->num_digits - j - 1;
			size_t number_pos = number->num_digits - (i + j) - 1;

			number->digits[number_pos] += carry + lhs->digits[lhs_pos] * rhs->digits[rhs_pos];
			carry = number->digits[number_pos] / NUMBER_BASE;
			number->digits[number_pos] %= NUMBER_BASE;
		}

		if (carry != 0) 
		{
			size_t number_pos = number->num_digits - (i + rhs->num_digits) - 1;
			number->digits[number_pos] += carry;
		}
	}

	if (inverse) 
	{
		number->is_negative = true;
	}

	number_delete_leading_zeros(number);

	return number;

}

struct number* number_div(struct number* nominator, struct number* denominator) 
{
	if (denominator->num_digits == 0) 
	{
		return NULL;
	}

	if (nominator->num_digits == 0) 
	{
		struct number* number = calloc(1, sizeof(struct number));
		if (number == NULL) {
			return NULL;
		}
		number->num_digits = 0;
		number->digits = NULL;
		number->is_negative = false;
		return number;
	}

	bool inverse = false;
	if (nominator->is_negative != denominator->is_negative) 
	{
		inverse = true;
	}

	bool nominator_sign = nominator->is_negative;
	nominator->is_negative = false;

	bool denominator_sign = denominator->is_negative;
	denominator->is_negative = false;

	struct number* pow10 = calloc(1, sizeof(struct number));
	if (pow10 == NULL) 
	{
		return NULL;
	}

	pow10->num_digits = nominator->num_digits + 2;
	pow10->digits = calloc(pow10->num_digits, sizeof(uint64_t));
	if (pow10->digits == NULL) 
	{
		free(pow10);
		return NULL;
	}
	pow10->digits[0] = 1;

	struct number* result = calloc(1, sizeof(struct number));
	if (result == NULL) 
	{
		free(pow10->digits);
		free(pow10);
	}

	{
		size_t num_digits_left = 0;                  // nominator / denominator >= NUMBER_BASE^(num_digits_left-1)
		size_t num_digits_right = pow10->num_digits; // nominator / denominator  < NUMBER_BASE^(num_digits_right-1)

		while (num_digits_left + 1 < num_digits_right) 
		{
			size_t mid = (num_digits_left + num_digits_right) / 2;

			pow10->num_digits = mid;

			struct number* mul_result = number_mul(denominator, pow10);

			if (mul_result == NULL) 
			{
				free(pow10->digits);
				free(pow10);
				return NULL;
			}

			if (number_compare(nominator, mul_result) >= 0) 
			{
				num_digits_left = mid;
			}
			else 
			{
				num_digits_right = mid;
			}

			mul_result = number_delete(mul_result);
		}

		result->num_digits = num_digits_left;
	}

	free(pow10->digits);
	free(pow10);

	if (result->num_digits == 0) 
	{
		result->digits = NULL;
		result->is_negative = false;

		nominator->is_negative = nominator_sign;
		denominator->is_negative = denominator_sign;

		return result;
	}

	result->digits = calloc(result->num_digits, sizeof(uint64_t));
	if (result->digits == NULL) 
	{
		nominator->is_negative = nominator_sign;
		denominator->is_negative = denominator_sign;
		free(result);
		return NULL;
	}

	for (size_t i = 0; i < result->num_digits; ++i) 
	{
		uint64_t digit_left = 0;            // <=
		uint64_t digit_right = NUMBER_BASE; // >

		while (digit_left + 1 < digit_right) 
		{
			uint64_t mid = (digit_left + digit_right) / 2;
			result->digits[i] = mid;

			struct number* mul_result = number_mul(denominator, result);

			if (mul_result == NULL) 
			{
				free(pow10->digits);
				free(pow10);
				return NULL;
			}

			if (number_compare(nominator, mul_result) >= 0) 
			{
				digit_left = mid;
			}
			else 
			{
				digit_right = mid;
			}

			mul_result = number_delete(mul_result);
		}

		result->digits[i] = digit_left;
	}

	if (inverse) 
	{
		result->is_negative = true;
	}

	nominator->is_negative = nominator_sign;
	denominator->is_negative = denominator_sign;

	return result;
}



