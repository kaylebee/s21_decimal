#include "extended_decimal.h"

void decimal_to_extended_decimal(s21_decimal value_1,
                                 s21_extended_decimal *value_2) {
  for (int i = 0; i < 3; i++) {
    value_2->bits[i] = value_1.bits[i];
  }
  value_2->bits[6] = value_1.bits[3];
}

void extended_decimal_to_decimal(s21_extended_decimal value_1,
                                 s21_decimal *value_2) {
  for (int i = 0; i < 3; i++) {
    value_2->bits[i] = value_1.bits[i];
  }
  value_2->bits[3] = value_1.bits[6];
}

void copy_extended_decimal(s21_extended_decimal value_1,
                           s21_extended_decimal *value_2) {
  for (int i = 0; i < 7; i++) {
    value_2->bits[i] = value_1.bits[i];
  }
}

void inverse_extended_decimal(s21_extended_decimal *value) {
  for (int i = 0; i < 6; i++) {
    value->bits[i] = ~value->bits[i];
  }
  extended_decimal_plus_one(value);
}

void mantissa_set_default(s21_extended_decimal *value) {
  for (size_t i = 0; i < 6; i++) {
    value->bits[i] = 0;
  }
}