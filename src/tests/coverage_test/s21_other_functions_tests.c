#include "s21_tests.h"

/*
 *  Min, Max and Zero decimal values
 */

START_TEST(floor_test_0) {
  s21_decimal result_1 = {0};
  s21_decimal result_2 = {0};
  s21_decimal result_3 = {0};

  s21_floor(zero_dec, &result_1);
  s21_floor(max_dec, &result_2);
  s21_floor(min_dec, &result_3);

  ck_assert_int_eq(1, s21_is_equal(zero_dec, result_1));
  ck_assert_int_eq(1, s21_is_equal(max_dec, result_2));
  ck_assert_int_eq(1, s21_is_equal(min_dec, result_3));
}
END_TEST

START_TEST(round_test_0) {
  s21_decimal result_1 = {0};
  s21_decimal result_2 = {0};
  s21_decimal result_3 = {0};

  s21_round(zero_dec, &result_1);
  s21_round(max_dec, &result_2);
  s21_round(min_dec, &result_3);

  ck_assert_int_eq(1, s21_is_equal(zero_dec, result_1));
  ck_assert_int_eq(1, s21_is_equal(max_dec, result_2));
  ck_assert_int_eq(1, s21_is_equal(min_dec, result_3));
}
END_TEST

START_TEST(truncate_test_0) {
  s21_decimal result_1 = {0};
  s21_decimal result_2 = {0};
  s21_decimal result_3 = {0};

  s21_truncate(zero_dec, &result_1);
  s21_truncate(max_dec, &result_2);
  s21_truncate(min_dec, &result_3);

  ck_assert_int_eq(1, s21_is_equal(zero_dec, result_1));
  ck_assert_int_eq(1, s21_is_equal(max_dec, result_2));
  ck_assert_int_eq(1, s21_is_equal(min_dec, result_3));
}
END_TEST

START_TEST(negate_test_0) {
  s21_decimal result_1 = {0};
  s21_decimal result_2 = {0};
  s21_decimal result_3 = {0};

  s21_negate(zero_dec, &result_1);
  s21_negate(max_dec, &result_2);
  s21_negate(min_dec, &result_3);

  ck_assert_int_eq(NEGATIVE, result_1.bytes[SIGN]);
  ck_assert_int_eq(NEGATIVE, result_2.bytes[SIGN]);
  ck_assert_int_eq(0, result_3.bytes[SIGN]);
}
END_TEST

/*
 *  Rounding test
 */

START_TEST(floor_test_1) {
  s21_decimal value_1 = {{144}};
  s21_decimal value_2 = {{145}};
  s21_decimal value_3 = {{146}};

  s21_decimal original = {{14}};

  value_1.bytes[EXP] = 1;
  value_2.bytes[EXP] = 1;
  value_3.bytes[EXP] = 1;

  s21_floor(value_1, &value_1);
  s21_floor(value_2, &value_2);
  s21_floor(value_3, &value_3);

  ck_assert_int_eq(1, s21_is_equal(original, value_1));
  ck_assert_int_eq(1, s21_is_equal(original, value_2));
  ck_assert_int_eq(1, s21_is_equal(original, value_3));
}
END_TEST

START_TEST(round_test_1) {
  s21_decimal value_1 = {{144}};
  s21_decimal value_2 = {{145}};
  s21_decimal value_3 = {{146}};

  s21_decimal original_1 = {{14}};
  s21_decimal original_2 = {{15}};
  s21_decimal original_3 = {{15}};

  value_1.bytes[EXP] = 1;
  value_2.bytes[EXP] = 1;
  value_3.bytes[EXP] = 1;

  s21_round(value_1, &value_1);
  s21_round(value_2, &value_2);
  s21_round(value_3, &value_3);

  ck_assert_int_eq(1, s21_is_equal(original_1, value_1));
  ck_assert_int_eq(1, s21_is_equal(original_2, value_2));
  ck_assert_int_eq(1, s21_is_equal(original_3, value_3));
}
END_TEST

START_TEST(truncate_test_1) {
  s21_decimal value_1 = {{144}};
  s21_decimal value_2 = {{145}};
  s21_decimal value_3 = {{146}};

  s21_decimal original = {{14}};

  value_1.bytes[EXP] = 1;
  value_2.bytes[EXP] = 1;
  value_3.bytes[EXP] = 1;

  s21_truncate(value_1, &value_1);
  s21_truncate(value_2, &value_2);
  s21_truncate(value_3, &value_3);

  ck_assert_int_eq(1, s21_is_equal(original, value_1));
  ck_assert_int_eq(1, s21_is_equal(original, value_2));
  ck_assert_int_eq(1, s21_is_equal(original, value_3));
}
END_TEST

/*
 *  Rounding test with negative values
 */

START_TEST(floor_test_2) {
  s21_decimal value_1 = {{144}};
  s21_decimal value_2 = {{145}};
  s21_decimal value_3 = {{146}};

  s21_decimal original = {{15}};
  original.bytes[SIGN] = NEGATIVE;

  value_1.bytes[EXP] = 1;
  value_2.bytes[EXP] = 1;
  value_3.bytes[EXP] = 1;

  value_1.bytes[SIGN] = NEGATIVE;
  value_2.bytes[SIGN] = NEGATIVE;
  value_3.bytes[SIGN] = NEGATIVE;

  s21_floor(value_1, &value_1);
  s21_floor(value_2, &value_2);
  s21_floor(value_3, &value_3);

  ck_assert_int_eq(1, s21_is_equal(original, value_1));
  ck_assert_int_eq(1, s21_is_equal(original, value_2));
  ck_assert_int_eq(1, s21_is_equal(original, value_3));
}
END_TEST

START_TEST(round_test_2) {
  s21_decimal value_1 = {{144}};
  s21_decimal value_2 = {{145}};
  s21_decimal value_3 = {{146}};

  s21_decimal original_1 = {{14}};
  s21_decimal original_2 = {{15}};
  s21_decimal original_3 = {{15}};

  value_1.bytes[EXP] = 1;
  value_2.bytes[EXP] = 1;
  value_3.bytes[EXP] = 1;

  value_1.bytes[SIGN] = NEGATIVE;
  value_2.bytes[SIGN] = NEGATIVE;
  value_3.bytes[SIGN] = NEGATIVE;

  original_1.bytes[SIGN] = NEGATIVE;
  original_2.bytes[SIGN] = NEGATIVE;
  original_3.bytes[SIGN] = NEGATIVE;

  s21_round(value_1, &value_1);
  s21_round(value_2, &value_2);
  s21_round(value_3, &value_3);

  ck_assert_int_eq(1, s21_is_equal(original_1, value_1));
  ck_assert_int_eq(1, s21_is_equal(original_2, value_2));
  ck_assert_int_eq(1, s21_is_equal(original_3, value_3));
}
END_TEST

START_TEST(truncate_test_2) {
  s21_decimal value_1 = {{144}};
  s21_decimal value_2 = {{145}};
  s21_decimal value_3 = {{146}};

  s21_decimal original = {{14}};
  original.bytes[SIGN] = NEGATIVE;

  value_1.bytes[EXP] = 1;
  value_2.bytes[EXP] = 1;
  value_3.bytes[EXP] = 1;

  value_1.bytes[SIGN] = NEGATIVE;
  value_2.bytes[SIGN] = NEGATIVE;
  value_3.bytes[SIGN] = NEGATIVE;

  s21_truncate(value_1, &value_1);
  s21_truncate(value_2, &value_2);
  s21_truncate(value_3, &value_3);

  ck_assert_int_eq(1, s21_is_equal(original, value_1));
  ck_assert_int_eq(1, s21_is_equal(original, value_2));
  ck_assert_int_eq(1, s21_is_equal(original, value_3));
}
END_TEST

Suite *s21_other_functions_tests(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_other_functions_tests");
  tc = tcase_create("core");

  suite_add_tcase(s, tc);

  tcase_add_test(tc, floor_test_0);
  tcase_add_test(tc, round_test_0);
  tcase_add_test(tc, truncate_test_0);
  tcase_add_test(tc, negate_test_0);

  tcase_add_test(tc, floor_test_1);
  tcase_add_test(tc, round_test_1);
  tcase_add_test(tc, truncate_test_1);

  tcase_add_test(tc, floor_test_2);
  tcase_add_test(tc, round_test_2);
  tcase_add_test(tc, truncate_test_2);

  return s;
}