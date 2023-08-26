#include "s21_tests.h"

/*
 *  Comparison Min, Max and Zero decimal values
 */

START_TEST(is_less_test_0) {
  ck_assert_int_eq(0, s21_is_less(zero_dec, zero_dec));
  ck_assert_int_eq(0, s21_is_less(max_dec, max_dec));
  ck_assert_int_eq(0, s21_is_less(min_dec, min_dec));

  ck_assert_int_eq(1, s21_is_less(zero_dec, max_dec));
  ck_assert_int_eq(0, s21_is_less(zero_dec, min_dec));

  ck_assert_int_eq(0, s21_is_less(max_dec, zero_dec));
  ck_assert_int_eq(0, s21_is_less(max_dec, min_dec));

  ck_assert_int_eq(1, s21_is_less(min_dec, zero_dec));
  ck_assert_int_eq(1, s21_is_less(min_dec, max_dec));
}
END_TEST

START_TEST(is_less_or_equal_test_0) {
  ck_assert_int_eq(1, s21_is_less_or_equal(zero_dec, zero_dec));
  ck_assert_int_eq(1, s21_is_less_or_equal(max_dec, max_dec));
  ck_assert_int_eq(1, s21_is_less_or_equal(min_dec, min_dec));

  ck_assert_int_eq(1, s21_is_less_or_equal(zero_dec, max_dec));
  ck_assert_int_eq(0, s21_is_less_or_equal(zero_dec, min_dec));

  ck_assert_int_eq(0, s21_is_less_or_equal(max_dec, zero_dec));
  ck_assert_int_eq(0, s21_is_less_or_equal(max_dec, min_dec));

  ck_assert_int_eq(1, s21_is_less_or_equal(min_dec, zero_dec));
  ck_assert_int_eq(1, s21_is_less_or_equal(min_dec, max_dec));
}
END_TEST

START_TEST(is_greater_test_0) {
  ck_assert_int_eq(0, s21_is_greater(zero_dec, zero_dec));
  ck_assert_int_eq(0, s21_is_greater(max_dec, max_dec));
  ck_assert_int_eq(0, s21_is_greater(min_dec, min_dec));

  ck_assert_int_eq(0, s21_is_greater(zero_dec, max_dec));
  ck_assert_int_eq(1, s21_is_greater(zero_dec, min_dec));

  ck_assert_int_eq(1, s21_is_greater(max_dec, zero_dec));
  ck_assert_int_eq(1, s21_is_greater(max_dec, min_dec));

  ck_assert_int_eq(0, s21_is_greater(min_dec, zero_dec));
  ck_assert_int_eq(0, s21_is_greater(min_dec, max_dec));
}
END_TEST

START_TEST(is_greater_or_equal_test_0) {
  ck_assert_int_eq(1, s21_is_greater_or_equal(zero_dec, zero_dec));
  ck_assert_int_eq(1, s21_is_greater_or_equal(max_dec, max_dec));
  ck_assert_int_eq(1, s21_is_greater_or_equal(min_dec, min_dec));

  ck_assert_int_eq(0, s21_is_greater_or_equal(zero_dec, max_dec));
  ck_assert_int_eq(1, s21_is_greater_or_equal(zero_dec, min_dec));

  ck_assert_int_eq(1, s21_is_greater_or_equal(max_dec, zero_dec));
  ck_assert_int_eq(1, s21_is_greater_or_equal(max_dec, min_dec));

  ck_assert_int_eq(0, s21_is_greater_or_equal(min_dec, zero_dec));
  ck_assert_int_eq(0, s21_is_greater_or_equal(min_dec, max_dec));
}
END_TEST

START_TEST(is_equal_test_0) {
  ck_assert_int_eq(1, s21_is_equal(zero_dec, zero_dec));
  ck_assert_int_eq(1, s21_is_equal(max_dec, max_dec));
  ck_assert_int_eq(1, s21_is_equal(min_dec, min_dec));

  ck_assert_int_eq(0, s21_is_equal(zero_dec, max_dec));
  ck_assert_int_eq(0, s21_is_equal(zero_dec, min_dec));

  ck_assert_int_eq(0, s21_is_equal(max_dec, zero_dec));
  ck_assert_int_eq(0, s21_is_equal(max_dec, min_dec));

  ck_assert_int_eq(0, s21_is_equal(min_dec, zero_dec));
  ck_assert_int_eq(0, s21_is_equal(min_dec, max_dec));
}
END_TEST

START_TEST(is_not_equal_test_0) {
  ck_assert_int_eq(0, s21_is_not_equal(zero_dec, zero_dec));
  ck_assert_int_eq(0, s21_is_not_equal(max_dec, max_dec));
  ck_assert_int_eq(0, s21_is_not_equal(min_dec, min_dec));

  ck_assert_int_eq(1, s21_is_not_equal(zero_dec, max_dec));
  ck_assert_int_eq(1, s21_is_not_equal(zero_dec, min_dec));

  ck_assert_int_eq(1, s21_is_not_equal(max_dec, zero_dec));
  ck_assert_int_eq(1, s21_is_not_equal(max_dec, min_dec));

  ck_assert_int_eq(1, s21_is_not_equal(min_dec, zero_dec));
  ck_assert_int_eq(1, s21_is_not_equal(min_dec, max_dec));
}
END_TEST

/*
 *  All comparison functions in loop
 */

START_TEST(comparison_test_0) {
  for (int32_t i = -10; i <= 10; i++) {
    for (int32_t j = -10; j <= 10; j++) {
      s21_decimal val_1 = {0};
      s21_decimal val_2 = {0};

      s21_from_int_to_decimal(i, &val_1);
      s21_from_int_to_decimal(j, &val_2);

      ck_assert_int_eq(i < j, s21_is_less(val_1, val_2));
      ck_assert_int_eq(i <= j, s21_is_less_or_equal(val_1, val_2));
      ck_assert_int_eq(i > j, s21_is_greater(val_1, val_2));
      ck_assert_int_eq(i >= j, s21_is_greater_or_equal(val_1, val_2));
      ck_assert_int_eq(i == j, s21_is_equal(val_1, val_2));
      ck_assert_int_eq(i != j, s21_is_not_equal(val_1, val_2));
    }
  }
}
END_TEST

Suite *s21_comparison_tests(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_comparison_tests");
  tc = tcase_create("core");

  suite_add_tcase(s, tc);

  tcase_add_test(tc, comparison_test_0);

  tcase_add_test(tc, is_less_test_0);
  tcase_add_test(tc, is_less_or_equal_test_0);
  tcase_add_test(tc, is_greater_test_0);
  tcase_add_test(tc, is_greater_or_equal_test_0);
  tcase_add_test(tc, is_equal_test_0);
  tcase_add_test(tc, is_not_equal_test_0);

  return s;
}