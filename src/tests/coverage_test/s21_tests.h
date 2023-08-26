#ifndef TESTS_S21_TESTS_H
#define TESTS_S21_TESTS_H

#include <check.h>
#include <limits.h>
#include <stdio.h>

#include "../../lib/extended_decimal.h"
#include "../../s21_decimal.h"

static s21_decimal zero_dec = {{0, 0, 0, 0}};
static s21_decimal max_dec = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
static s21_decimal min_dec = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};

SRunner *default_srunner_create();

Suite *s21_arithmetic_tests(void);
Suite *s21_comparison_tests(void);
Suite *s21_other_functions_tests(void);
Suite *s21_converters_tests(void);

#endif // TESTS_S21_TESTS_H