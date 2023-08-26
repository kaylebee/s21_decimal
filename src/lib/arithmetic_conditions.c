#include "extended_decimal.h"

int8_t sum_conditions(s21_decimal value_1, s21_decimal value_2,
                      s21_decimal *result) {
  int8_t status = 0;

  if (s21_is_zero(value_1)) {
    copy_decimal(value_2, result);
  } else if (s21_is_zero(value_2)) {
    copy_decimal(value_1, result);
  } else {
    status = 1;
  }
  return status;
}

int8_t mul_conditions(s21_decimal value_1, s21_decimal value_2,
                      s21_decimal *result) {
  int8_t status = 0;
  s21_decimal one_num = {{1}};

  if (s21_is_zero(value_1) || s21_is_zero(value_2)) {
    set_default(result);
  } else if (s21_is_equal(value_1, one_num)) {
    copy_decimal(value_2, result);
  } else if (s21_is_equal(value_2, one_num)) {
    copy_decimal(value_1, result);
  } else {
    status = 1;
  }
  return status;
}

int8_t div_conditions(s21_decimal value_1, s21_decimal value_2,
                      s21_decimal *result) {
  int8_t status = 0;
  s21_decimal one_num = {{1}};

  if (s21_is_zero(value_2)) {
    status = 3;
  } else if (s21_is_zero(value_1)) {
    set_default(result);
  } else if (s21_is_equal(value_2, one_num)) {
    copy_decimal(value_1, result);
  } else {
    status = 1;
  }
  return status;
}

int8_t mod_conditions(s21_decimal value_1, s21_decimal value_2,
                      s21_decimal *result) {
  return s21_div(value_1, value_2, result);
}