#include "extended_decimal.h"

int s21_is_less(s21_decimal num1, s21_decimal num2) {
  s21_extended_decimal big_num1 = {0};
  s21_extended_decimal big_num2 = {0};

  decimal_to_extended_decimal(num1, &big_num1);
  decimal_to_extended_decimal(num2, &big_num2);

  return extended_decimal_is_less(big_num1, big_num2);
}

int s21_is_less_or_equal(s21_decimal num1, s21_decimal num2) {
  return (s21_is_less(num1, num2) || s21_is_equal(num1, num2));
}

int s21_is_greater(s21_decimal num1, s21_decimal num2) {
  return s21_is_less(num2, num1);
}

int s21_is_greater_or_equal(s21_decimal num1, s21_decimal num2) {
  return !s21_is_less(num1, num2);
}

int s21_is_equal(s21_decimal num1, s21_decimal num2) {
  s21_extended_decimal big_num1 = {0};
  s21_extended_decimal big_num2 = {0};

  decimal_to_extended_decimal(num1, &big_num1);
  decimal_to_extended_decimal(num2, &big_num2);

  return extended_decimal_is_equal(big_num1, big_num2);
}

int s21_is_not_equal(s21_decimal num1, s21_decimal num2) {
  return !s21_is_equal(num1, num2);
}
