#include "extended_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  set_default(dst);

  if (src < 0) {
    src *= -1;
    dst->bytes[SIGN] = NEGATIVE;
  }
  dst->bits[0] = src;

  return 0;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int status = 0;
  set_default(dst);

  status = check_conditions_to_decimal(src);

  if (status == 0) {
    if (src < 0) {
      dst->bytes[SIGN] = NEGATIVE;
      src *= -1;
    }

    int scale = 0;
    double whole_part = normalize(src, &scale);

    write_normalized(dst, whole_part, scale);
  }

  return status;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int status = 0;

  if (src.bytes[EXP] > 0) {
    s21_truncate(src, &src);
  }

  if (src.bits[1] || src.bits[2]) {
    status = 1;
  } else {
    *dst = src.bits[0];
    if (src.bytes[SIGN] == NEGATIVE) {
      *dst *= -1;
    }
  }

  return status;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int status = 0;
  long double result = 0.0l;

  // convert mantissa to integer value, stored in result variable
  for (size_t i = 0; i < 96; i++) {
    if (src.bytes[i / 8] & (1 << i % 8)) {
      result += powl(2.0l, (long double)i);
    }
  }

  // bring the number accordance to the exponent
  for (int exponent = src.bytes[EXP]; exponent > 0; exponent--) {
    result /= 10.0l;
  }

  *dst = (float)result;
  *dst *= src.bytes[SIGN] & NEGATIVE ? -1 : 1;

  return status;
}
