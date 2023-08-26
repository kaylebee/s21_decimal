#include "extended_decimal.h"

void sum_extended_decimal(s21_extended_decimal value_1,
                          s21_extended_decimal value_2,
                          s21_extended_decimal *result) {
  mantissa_set_default(result);
  uint64_t transfer_bit = 0;

  for (int i = 0; i < 6; i++) {
    transfer_bit += (uint64_t)value_1.bits[i] + value_2.bits[i];
    result->bits[i] = transfer_bit;
    transfer_bit >>= 32;
  }
}

void sub_extended_decimal(s21_extended_decimal value_1,
                          s21_extended_decimal value_2,
                          s21_extended_decimal *result) {
  mantissa_set_default(result);
  inverse_extended_decimal(&value_1);
  sum_extended_decimal(value_1, value_2, result);
  inverse_extended_decimal(result);
}

void mul_extended_decimal(s21_extended_decimal value_1,
                          s21_extended_decimal value_2,
                          s21_extended_decimal *result) {
  mantissa_set_default(result);

  for (int16_t i = get_start_bit_extended_decimal(value_2); i >= 0; i--) {
    if (value_2.bits[0] & 1) {
      sum_extended_decimal(value_1, *result, result);
    }
    left_offset_extended_decimal(&value_1, 1);
    right_offset_extended_decimal(&value_2, 1);
  }
  result->bytes[BIG_EXP] = value_1.bytes[BIG_EXP] + value_2.bytes[BIG_EXP];
}

void div_extended_decimal(s21_extended_decimal value_1,
                          s21_extended_decimal value_2,
                          s21_extended_decimal *result) {
  mantissa_set_default(result);
  cast_to_one_exp(&value_1, &value_2);

  if (mantissa_comparison_extended_decimal(value_1, value_2) == 0) {
    result->bytes[0] = 1;
  } else {
    while (mantissa_comparison_extended_decimal(value_1, value_2) == 1) {
      mul10_extended_decimal(&value_1);
      result->bytes[BIG_EXP]++;
    }

    int_division(&value_1, value_2, result);
    fract_division(&value_1, value_2, result);
  }
}

void mod_extended_decimal(s21_extended_decimal value_1,
                          s21_extended_decimal value_2,
                          s21_extended_decimal *result) {
  mantissa_set_default(result);
  int_division(&value_1, value_2, result);
  copy_extended_decimal(value_1, result);
}