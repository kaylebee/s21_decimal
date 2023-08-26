#include "extended_decimal.h"

void overflow_round(s21_extended_decimal value, s21_extended_decimal *result) {
  s21_extended_decimal mod = {0};

  uint8_t start_bit = get_start_bit_extended_decimal(value);
  int8_t exponent = value.bytes[BIG_EXP];

  while ((start_bit >= 96 && exponent > 0) || exponent > 28) {
    div10_and_record_mod10(&value, &mod);

    start_bit = get_start_bit_extended_decimal(value);
    exponent--;
  }
  switch_round(&value, mod, BANK);
  copy_extended_decimal(value, result);
}

void round_to_int(s21_extended_decimal *value, int8_t type) {
  s21_extended_decimal mod = {0};

  while (value->bytes[BIG_EXP] > 0 && !extended_decimal_is_zero(*value)) {
    div10_and_record_mod10(value, &mod);
  }

  switch_round(value, mod, type);
}

void div10_and_record_mod10(s21_extended_decimal *value,
                            s21_extended_decimal *mod) {
  int8_t record_not_zero_mod = mod->bytes[25];
  mod10_extended_decimal(*value, mod);
  div10_extended_decimal(value);

  if (mod->bits[0] != 0) {
    record_not_zero_mod++;
  }
  mod->bytes[25] = record_not_zero_mod;
}

void switch_round(s21_extended_decimal *value, s21_extended_decimal mod,
                  int8_t type) {
  if (type == FLOOR) {
    floor_round(value, mod);
  } else if (type == BANK) {
    bank_round(value, mod);
  } else if (type == MATH) {
    math_round(value, mod);
  }
}

void bank_round(s21_extended_decimal *value, s21_extended_decimal mod) {
  if (mod.bits[0] == 5 && mod.bytes[25] == 1) {
    if (value->bytes[0] & 1) {
      extended_decimal_plus_one(value);
    }
  } else {
    math_round(value, mod);
  }
}

void math_round(s21_extended_decimal *value, s21_extended_decimal mod) {
  if (mod.bits[0] > 4) {
    extended_decimal_plus_one(value);
  }
}

void floor_round(s21_extended_decimal *value, s21_extended_decimal mod) {
  if (value->bytes[BIG_SIGN] == NEGATIVE && mod.bits[0] > 0) {
    extended_decimal_plus_one(value);
  }
}
