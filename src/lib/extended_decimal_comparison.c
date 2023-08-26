#include "extended_decimal.h"

int8_t byte_comparison_extended_decimal(s21_extended_decimal num1,
                                        s21_extended_decimal num2,
                                        int8_t indent) {
  int8_t result = 0;

  if (num1.bytes[indent] > num2.bytes[indent]) {
    result = -1;
  } else if (num1.bytes[indent] < num2.bytes[indent]) {
    result = 1;
  }
  return result;
}

int8_t mantissa_comparison_extended_decimal(s21_extended_decimal num1,
                                            s21_extended_decimal num2) {
  int8_t result = 0;

  for (int i = 23; i >= 0 && result == 0; i--) {
    result = byte_comparison_extended_decimal(num1, num2, i);
  }
  return result;
}

int8_t extended_decimal_is_zero(s21_extended_decimal num) {
  int8_t result = 0;
  s21_extended_decimal zero_num = {0};

  return !mantissa_comparison_extended_decimal(num, zero_num);
}

int8_t extended_decimal_is_less(s21_extended_decimal num1,
                                s21_extended_decimal num2) {
  int8_t result = 0;

  if (!(extended_decimal_is_zero(num1) == 1 &&
        extended_decimal_is_zero(num2) == 1)) {
    cast_to_one_exp(&num1, &num2);
    result = byte_comparison_extended_decimal(num1, num2, BIG_SIGN) * -1;

    if (result == 0) {
      int8_t greater_mantissa =
          mantissa_comparison_extended_decimal(num1, num2);

      if (num1.bytes[BIG_SIGN] == NEGATIVE) {
        greater_mantissa *= -1;
      }

      if (greater_mantissa == 1) {
        result = 1;
      }
    } else if (result == -1) {
      result = 0;
    }
  }
  return result;
}

int8_t extended_decimal_is_equal(s21_extended_decimal num1,
                                 s21_extended_decimal num2) {
  int8_t result = 1;

  cast_to_one_exp(&num1, &num2);
  for (int8_t i = 0; i < 7; i++) {
    if (num1.bits[i] != num2.bits[i]) {
      result = 0;
      break;
    }
  }
  return result;
}