#ifndef LIB_EXTENDED_DECIMAL_H
#define LIB_EXTENDED_DECIMAL_H

#include "../s21_decimal.h"

#define BIG_SIGN 27
#define BIG_EXP 26

typedef union s21_extended_decimal {
  uint8_t bytes[28];
  uint32_t bits[7];
} s21_extended_decimal;

#define MATH 0
#define BANK 1
#define FLOOR 2
#define TRUNCATE 3

#define ROUND_TO_INT(type)                                                     \
  if (value.bytes[EXP] > 0) {                                                  \
    s21_extended_decimal big_value = {0};                                      \
    decimal_to_extended_decimal(value, &big_value);                            \
    round_to_int(&big_value, type);                                            \
    extended_decimal_to_decimal(big_value, result);                            \
  } else {                                                                     \
    copy_decimal(value, result);                                               \
  }                                                                            \
  return 0

#define ADD add_set_sign(big_value_1, big_value_2, &big_result);
#define MUL mul_extended_decimal(big_value_1, big_value_2, &big_result);
#define DIV div_extended_decimal(big_value_1, big_value_2, &big_result);
#define MOD mod_extended_decimal(big_value_1, big_value_2, &big_result);

#define MATH_OPERATION(operation)                                              \
  decimal_to_extended_decimal(value_1, &big_value_1);                          \
  decimal_to_extended_decimal(value_2, &big_value_2);                          \
  cast_to_one_exp(&big_value_1, &big_value_2);                                 \
  operation overflow_round(big_result, &big_result);                           \
  clear_trailing_zeros(&big_result);                                           \
  extended_decimal_to_decimal(big_result, result);

void sum_extended_decimal(s21_extended_decimal value_1,
                          s21_extended_decimal value_2,
                          s21_extended_decimal *result);
void sub_extended_decimal(s21_extended_decimal value_1,
                          s21_extended_decimal value_2,
                          s21_extended_decimal *result);
void mul_extended_decimal(s21_extended_decimal value_1,
                          s21_extended_decimal value_2,
                          s21_extended_decimal *result);
void div_extended_decimal(s21_extended_decimal value_1,
                          s21_extended_decimal value_2,
                          s21_extended_decimal *result);
void mod_extended_decimal(s21_extended_decimal value_1,
                          s21_extended_decimal value_2,
                          s21_extended_decimal *result);

int8_t sum_conditions(s21_decimal value_1, s21_decimal value_2,
                      s21_decimal *result);
int8_t mul_conditions(s21_decimal value_1, s21_decimal value_2,
                      s21_decimal *result);
int8_t div_conditions(s21_decimal value_1, s21_decimal value_2,
                      s21_decimal *result);
int8_t mod_conditions(s21_decimal value_1, s21_decimal value_2,
                      s21_decimal *result);

void add_set_sign(s21_extended_decimal value_1, s21_extended_decimal value_2,
                  s21_extended_decimal *result);

void int_division(s21_extended_decimal *value_1, s21_extended_decimal value_2,
                  s21_extended_decimal *result);
void fract_division(s21_extended_decimal *value_1, s21_extended_decimal value_2,
                    s21_extended_decimal *result);
void extended_decimal_plus_one(s21_extended_decimal *result);
void div10_extended_decimal(s21_extended_decimal *value);
void mul10_extended_decimal(s21_extended_decimal *value);
void mod10_extended_decimal(s21_extended_decimal value,
                            s21_extended_decimal *result);

void extended_decimal_to_decimal(s21_extended_decimal value_1,
                                 s21_decimal *value_2);
void decimal_to_extended_decimal(s21_decimal value_1,
                                 s21_extended_decimal *value_2);
void copy_extended_decimal(s21_extended_decimal value_1,
                           s21_extended_decimal *value_2);
void inverse_extended_decimal(s21_extended_decimal *value);
void mantissa_set_default(s21_extended_decimal *value);

int8_t byte_comparison_extended_decimal(s21_extended_decimal num1,
                                        s21_extended_decimal num2,
                                        int8_t indent);
int8_t mantissa_comparison_extended_decimal(s21_extended_decimal num1,
                                            s21_extended_decimal num2);
int8_t extended_decimal_is_zero(s21_extended_decimal num);
int8_t extended_decimal_is_less(s21_extended_decimal num1,
                                s21_extended_decimal num2);
int8_t extended_decimal_is_equal(s21_extended_decimal num1,
                                 s21_extended_decimal num2);

void overflow_round(s21_extended_decimal value, s21_extended_decimal *result);
void div10_and_record_mod10(s21_extended_decimal *value,
                            s21_extended_decimal *mod);
void switch_round(s21_extended_decimal *value, s21_extended_decimal mod,
                  int8_t type);
void round_to_int(s21_extended_decimal *value, int8_t type);
void bank_round(s21_extended_decimal *value, s21_extended_decimal mod);
void math_round(s21_extended_decimal *value, s21_extended_decimal mod);
void floor_round(s21_extended_decimal *value, s21_extended_decimal mod);

void cast_to_one_exp(s21_extended_decimal *value_1,
                     s21_extended_decimal *value_2);
void right_offset_extended_decimal(s21_extended_decimal *value,
                                   uint8_t size_offset);
void left_offset_extended_decimal(s21_extended_decimal *value,
                                  uint8_t size_offset);
void clear_trailing_zeros(s21_extended_decimal *value_1);
uint8_t get_start_byte_extended_decimal(s21_extended_decimal value);
uint8_t get_start_bit_extended_decimal(s21_extended_decimal value);
void set_status(s21_extended_decimal big_result, s21_decimal *result,
                int8_t *status);

#endif // LIB_EXTENDED_DECIMAL_H
