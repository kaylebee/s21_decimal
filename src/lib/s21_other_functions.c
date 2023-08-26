#include "extended_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) { ROUND_TO_INT(FLOOR); }

int s21_round(s21_decimal value, s21_decimal *result) { ROUND_TO_INT(MATH); }

int s21_truncate(s21_decimal value, s21_decimal *result) {
  ROUND_TO_INT(TRUNCATE);
}

int s21_negate(s21_decimal value, s21_decimal *result) {
  value.bytes[SIGN] ^= NEGATIVE;
  copy_decimal(value, result);

  return 0;
}
