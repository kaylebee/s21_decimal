#include "extended_decimal.h"

int s21_is_zero(s21_decimal num) {
  return (!num.bits[0] && !num.bits[1] && !num.bits[2]);
}

void copy_decimal(s21_decimal value, s21_decimal *result) {
  for (size_t i = 0; i < 4; i++) {
    result->bits[i] = value.bits[i];
  }
}

void set_default(s21_decimal *src) {
  for (size_t i = 0; i < 16; i++) {
    src->bytes[i] = 0;
  }
}

void write_normalized(s21_decimal *dst, double number, int exponent) {
  int length = get_whole_part_length(number);
  s21_extended_decimal extended_dst = {0};

  if (length <= FLOAT_DIGITS) {
    dst->bits[0] = (int)number;
    dst->bytes[EXP] = exponent;
    decimal_to_extended_decimal(*dst, &extended_dst);
  } else {
    int diff = length - FLOAT_DIGITS;

    number /= pow(10.0, diff);
    dst->bits[0] = (int)number;

    decimal_to_extended_decimal(*dst, &extended_dst);

    while (diff > 0) {
      mul10_extended_decimal(&extended_dst);
      diff--;
    }

    extended_dst.bytes[BIG_EXP] = exponent;
  }

  clear_trailing_zeros(&extended_dst);
  extended_decimal_to_decimal(extended_dst, dst);
}

int get_whole_part_length(double value) {
  return (value == 0.0) ? 1 : log10(round(value)) + 1;
}

int check_conditions_to_decimal(float src) {
  int status = 0;

  if ((src >= MAX_DECIMAL) || (src <= MIN_DECIMAL) ||
      (fabsf(src) < pow(10.0f, (float)-28.0)) || (src == INFINITY) ||
      (src == -INFINITY)) {
    status = 1;
  }

  return status;
}

double normalize(float src, int *scale) {
  double power = 10.0;

  double whole_part = round((double)src);
  double fract_part = (double)src - whole_part;

  int whole_part_size = get_whole_part_length(whole_part);
  if (whole_part_size < 8) {
    while (whole_part_size < 8 && *scale < 28) {
      whole_part = whole_part * power + round(fract_part * power);
      fract_part *= power;
      fract_part -= round(fract_part);
      whole_part_size = get_whole_part_length(whole_part);
      *scale += 1;
      if (fract_part == 0) {
        break;
      }
    }
  }

  whole_part_size = get_whole_part_length(whole_part);
  if (whole_part_size > FLOAT_DIGITS) {
    int diff = whole_part_size - FLOAT_DIGITS;
    whole_part = round(whole_part / pow(power, diff)) * pow(power, diff);
  }

  return whole_part;
}
