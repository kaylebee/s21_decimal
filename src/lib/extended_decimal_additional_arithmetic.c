#include "extended_decimal.h"

void mul10_extended_decimal(s21_extended_decimal *value) {
  s21_extended_decimal tmp_value = {0};

  copy_extended_decimal(*value, &tmp_value);

  left_offset_extended_decimal(&tmp_value, 1);
  left_offset_extended_decimal(value, 3);

  sum_extended_decimal(*value, tmp_value, value);

  value->bytes[BIG_EXP]++;
}

void div10_extended_decimal(s21_extended_decimal *value) {
  s21_extended_decimal result = {0};
  s21_extended_decimal ten_num = {{10}};

  int8_t exponent = value->bytes[BIG_EXP] - 1;
  int8_t sign = value->bytes[BIG_SIGN];

  int_division(value, ten_num, &result);
  copy_extended_decimal(result, value);

  value->bytes[BIG_EXP] = exponent;
  value->bytes[BIG_SIGN] = sign;
}

void mod10_extended_decimal(s21_extended_decimal value,
                            s21_extended_decimal *result) {
  s21_extended_decimal ten_num = {{10}};
  mantissa_set_default(result);
  int_division(&value, ten_num, result);
  copy_extended_decimal(value, result);
}

void int_division(s21_extended_decimal *value_1, s21_extended_decimal value_2,
                  s21_extended_decimal *result) {
  mantissa_set_default(result);

  int16_t start_bit_1 = get_start_bit_extended_decimal(*value_1);
  int16_t start_bit_2 = get_start_bit_extended_decimal(value_2);
  int16_t min_start_bit_2 = start_bit_2;

  left_offset_extended_decimal(&value_2, start_bit_1 - start_bit_2);
  start_bit_2 = start_bit_1;

  while (mantissa_comparison_extended_decimal(*value_1, value_2) == 1) {
    right_offset_extended_decimal(&value_2, 1);
    start_bit_2--;
  }

  while (start_bit_2-- >= min_start_bit_2) {
    left_offset_extended_decimal(result, 1);
    if (mantissa_comparison_extended_decimal(*value_1, value_2) != 1) {
      sub_extended_decimal(*value_1, value_2, value_1);
      result->bytes[0] |= 1;
    }
    right_offset_extended_decimal(&value_2, 1);
  }
}

void fract_division(s21_extended_decimal *value_1, s21_extended_decimal value_2,
                    s21_extended_decimal *result) {
  while (!extended_decimal_is_zero(*value_1) &&
         get_start_bit_extended_decimal(*result) < 112) {
    s21_extended_decimal tmp_res = {0};

    mul10_extended_decimal(value_1);
    int_division(value_1, value_2, &tmp_res);

    mul10_extended_decimal(result);
    sum_extended_decimal(*result, tmp_res, result);
  }
}

void extended_decimal_plus_one(s21_extended_decimal *result) {
  s21_extended_decimal num = {{1}};
  sum_extended_decimal(*result, num, result);
}