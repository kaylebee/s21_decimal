#ifndef SRC_S21_DECIMAL_H
#define SRC_S21_DECIMAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <fcntl.h>
#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
 * A data type that is a 16-byte representation of a floating point number
 */
typedef union s21_decimal {
  uint32_t bits[4];
  uint8_t bytes[16];
} s21_decimal;

#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned long size_t;
#endif // _SIZE_T

#define SIGN 15
#define EXP 14
#define MANTISSA 11

#define NEGATIVE 0b10000000
#define FLOAT_DIGITS 7
#define MAX_DECIMAL powl(2.0, 96)
#define MIN_DECIMAL -1 * MAX_DECIMAL

// Converters
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

// Comparison
int s21_is_less(s21_decimal num1, s21_decimal num2);
int s21_is_less_or_equal(s21_decimal num1, s21_decimal num2);
int s21_is_greater(s21_decimal num1, s21_decimal num2);
int s21_is_greater_or_equal(s21_decimal num1, s21_decimal num2);
int s21_is_equal(s21_decimal num1, s21_decimal num2);
int s21_is_not_equal(s21_decimal num1, s21_decimal num2);

// Math operators
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// Other Functions
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

// Common
void write_normalized(s21_decimal *dst, double number, int exponent);
void copy_decimal(s21_decimal value, s21_decimal *result);
int get_whole_part_length(double value);
void set_default(s21_decimal *src);
int s21_is_zero(s21_decimal num);

int check_conditions_to_decimal(float src);
double normalize(float src, int *scale);

#ifdef __cplusplus
}
#endif

#endif // SRC_S21_DECIMAL_H
