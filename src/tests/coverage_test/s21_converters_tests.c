#include "s21_tests.h"

START_TEST(from_int_to_decimal_test_0) {
  s21_decimal decimal_number = {0};
  int32_t int_number = 0;

  for (int i = -10; i <= 10; i++) {
    int_number = i;
    ck_assert_int_eq(0, s21_from_int_to_decimal(int_number, &decimal_number));
    if (i < 0) {
      int_number *= -1;
    }
    ck_assert_int_eq(int_number, decimal_number.bits[0]);
  }
}
END_TEST

START_TEST(from_float_to_decimal_test_0) {
  s21_decimal decimal_number = {0};
  for (float i = -5.11; i <= 5.11; i += 0.789) {
    ck_assert_int_eq(0, s21_from_float_to_decimal(i, &decimal_number));
  }
}
END_TEST

START_TEST(from_float_to_decimal_test_2) {
  s21_decimal decimal_number = {0};
  ck_assert_int_eq(0, s21_from_float_to_decimal(75000000.0, &decimal_number));
  ck_assert_int_eq(0, s21_from_float_to_decimal(7.5, &decimal_number));
}
END_TEST

START_TEST(from_decimal_to_int_test_0) {
  s21_decimal decimal_number = {0};
  int32_t int_number = 0;

  for (int i = -10; i <= 10; i++) {
    decimal_number.bits[0] = i;
    if (i < 0) {
      decimal_number.bytes[SIGN] = NEGATIVE;
      decimal_number.bits[0] *= -1;
    } else {
      decimal_number.bytes[SIGN] = 0;
    }
    ck_assert_int_eq(0, s21_from_decimal_to_int(decimal_number, &int_number));

    if (i < 0) {
      int_number *= -1;
    }
    ck_assert_int_eq(int_number, decimal_number.bits[0]);
  }
}
END_TEST

START_TEST(from_decimal_to_float_test_0) {
  s21_decimal decimal_number = {0};
  float float_number = 0;
  for (int i = -5; i <= 5; i += 1) {
    decimal_number.bytes[EXP] = i * 2;
    ck_assert_int_eq(0,
                     s21_from_decimal_to_float(decimal_number, &float_number));
  }
}
END_TEST

START_TEST(from_float_to_decimal_test_1) {
  s21_decimal decimal_number = {0};

  float number = MAX_DECIMAL + 1;
  ck_assert_int_eq(1, s21_from_float_to_decimal(number, &decimal_number));

  number = MIN_DECIMAL - 1;
  ck_assert_int_eq(1, s21_from_float_to_decimal(number, &decimal_number));

  number = 1.676346734723483;
  ck_assert_int_eq(0, s21_from_float_to_decimal(number, &decimal_number));

  number = -1.676346734723483;
  ck_assert_int_eq(0, s21_from_float_to_decimal(number, &decimal_number));

  number = 1676346734723483.676346734723483;
  ck_assert_int_eq(0, s21_from_float_to_decimal(number, &decimal_number));

  number = -1676346734723483.676346734723483;
  ck_assert_int_eq(0, s21_from_float_to_decimal(number, &decimal_number));
}
END_TEST

START_TEST(from_decimal_to_int_test_1) {
  int number = 0;
  ck_assert_int_eq(1, s21_from_decimal_to_int(max_dec, &number));
  ck_assert_int_eq(1, s21_from_decimal_to_int(min_dec, &number));
  ck_assert_int_eq(0, s21_from_decimal_to_int(zero_dec, &number));

  s21_decimal max_decimal_number = {0};
  copy_decimal(max_dec, &max_decimal_number);
  max_decimal_number.bytes[EXP] = 28;

  s21_decimal min_decimal_number = {0};
  copy_decimal(max_dec, &min_decimal_number);
  min_decimal_number.bytes[EXP] = 28;

  ck_assert_int_eq(0, s21_from_decimal_to_int(max_decimal_number, &number));
  ck_assert_int_eq(0, s21_from_decimal_to_int(min_decimal_number, &number));
}
END_TEST

START_TEST(from_decimal_to_float_test_1) {
  float number = 0;
  ck_assert_int_eq(0, s21_from_decimal_to_float(max_dec, &number));
  ck_assert_int_eq(0, s21_from_decimal_to_float(min_dec, &number));
  ck_assert_int_eq(0, s21_from_decimal_to_float(zero_dec, &number));
  ck_assert_float_eq(0, number);
}
END_TEST

Suite *s21_converters_tests(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_converters_tests");
  tc = tcase_create("core");

  suite_add_tcase(s, tc);

  tcase_add_test(tc, from_int_to_decimal_test_0);
  tcase_add_test(tc, from_float_to_decimal_test_0);
  tcase_add_test(tc, from_decimal_to_int_test_0);
  tcase_add_test(tc, from_decimal_to_float_test_0);

  tcase_add_test(tc, from_float_to_decimal_test_1);
  tcase_add_test(tc, from_float_to_decimal_test_2);
  tcase_add_test(tc, from_decimal_to_int_test_1);
  tcase_add_test(tc, from_decimal_to_float_test_1);

  return s;
}