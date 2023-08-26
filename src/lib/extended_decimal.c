#include "extended_decimal.h"

void add_set_sign(s21_extended_decimal value_1, s21_extended_decimal value_2,
                  s21_extended_decimal *result) {
  if (value_1.bytes[BIG_SIGN] ^ value_2.bytes[BIG_SIGN]) {
    if (mantissa_comparison_extended_decimal(value_1, value_2) == -1) {
      sub_extended_decimal(value_1, value_2, result);
      result->bytes[BIG_SIGN] = value_1.bytes[BIG_SIGN];
    } else {
      sub_extended_decimal(value_2, value_1, result);
      result->bytes[BIG_SIGN] = value_2.bytes[BIG_SIGN];
    }
  } else {
    sum_extended_decimal(value_1, value_2, result);
    result->bytes[BIG_SIGN] = value_1.bytes[BIG_SIGN];
  }
  result->bytes[BIG_EXP] = value_1.bytes[BIG_EXP];
}

void cast_to_one_exp(s21_extended_decimal *value_1,
                     s21_extended_decimal *value_2) {
  int8_t exp_diff = value_1->bytes[BIG_EXP] - value_2->bytes[BIG_EXP];

  while (exp_diff < 0) {
    mul10_extended_decimal(value_1);
    exp_diff++;
  }
  while (exp_diff > 0) {
    mul10_extended_decimal(value_2);
    exp_diff--;
  }
}

void clear_trailing_zeros(s21_extended_decimal *value_1) {
  s21_extended_decimal mod = {0};

  mod10_extended_decimal(*value_1, &mod);
  while (extended_decimal_is_zero(mod) && value_1->bytes[BIG_EXP] > 0) {
    div10_extended_decimal(value_1);
    mod10_extended_decimal(*value_1, &mod);
  }
}

uint8_t get_start_bit_extended_decimal(s21_extended_decimal value) {
  uint8_t start_bit = 0;
  uint8_t tmp_bit = 0;
  uint8_t start_byte = get_start_byte_extended_decimal(value);

  for (; start_bit < 8 && tmp_bit == 0; start_bit++) {
    tmp_bit = value.bytes[start_byte] << start_bit;
    tmp_bit >>= 7;
  }
  return 8 - start_bit + start_byte * 8;
}

uint8_t get_start_byte_extended_decimal(s21_extended_decimal value) {
  uint8_t start_byte = 23;
  for (; start_byte > 0 && value.bytes[start_byte] == 0; start_byte--)
    ;
  return start_byte;
}

void left_offset_extended_decimal(s21_extended_decimal *value,
                                  uint8_t size_offset) {
  for (int i = 0; i < size_offset; i++) {
    value->bits[5] <<= 1;
    for (int j = 4; j >= 0; j--) {
      uint32_t first_bit = value->bits[j] & (1 << 31);
      value->bits[j + 1] |= (first_bit >> 31);
      value->bits[j] <<= 1;
    }
  }
}

void right_offset_extended_decimal(s21_extended_decimal *value,
                                   uint8_t size_offset) {
  for (int i = 0; i < size_offset; i++) {
    value->bits[0] >>= 1;
    for (int j = 1; j <= 5; j++) {
      uint32_t last_bit = value->bits[j] & 1;
      value->bits[j - 1] |= (last_bit << 31);
      value->bits[j] >>= 1;
    }
  }
}

void set_status(s21_extended_decimal big_result, s21_decimal *result,
                int8_t *status) {
  right_offset_extended_decimal(&big_result, 96);

  if (*status != 3 && extended_decimal_is_zero(big_result) == 0) {
    *status = 1;
    if (result->bytes[SIGN] == NEGATIVE) {
      *status = 2;
    }
    set_default(result);
  } else if (*status != 3) {
    *status = 0;
  }
}