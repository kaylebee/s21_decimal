#include "s21_tests.h"

/*
 *  Min, Max and Zero decimal values
 */

START_TEST(add_test_0) {
  s21_decimal result = {0};

  ck_assert_int_eq(0, s21_add(zero_dec, zero_dec, &result));
  ck_assert_int_eq(1, s21_add(max_dec, max_dec, &result));
  ck_assert_int_eq(2, s21_add(min_dec, min_dec, &result));

  ck_assert_int_eq(0, s21_add(zero_dec, max_dec, &result));
  ck_assert_int_eq(0, s21_add(zero_dec, min_dec, &result));

  ck_assert_int_eq(0, s21_add(max_dec, zero_dec, &result));
  ck_assert_int_eq(0, s21_add(max_dec, min_dec, &result));

  ck_assert_int_eq(0, s21_add(min_dec, zero_dec, &result));
  ck_assert_int_eq(0, s21_add(min_dec, max_dec, &result));
}
END_TEST

START_TEST(sub_test_0) {
  s21_decimal result = {0};

  ck_assert_int_eq(0, s21_sub(zero_dec, zero_dec, &result));
  ck_assert_int_eq(0, s21_sub(max_dec, max_dec, &result));
  ck_assert_int_eq(0, s21_sub(min_dec, min_dec, &result));

  ck_assert_int_eq(0, s21_sub(zero_dec, max_dec, &result));
  ck_assert_int_eq(0, s21_sub(zero_dec, min_dec, &result));

  ck_assert_int_eq(0, s21_sub(max_dec, zero_dec, &result));
  ck_assert_int_eq(1, s21_sub(max_dec, min_dec, &result));

  ck_assert_int_eq(0, s21_sub(min_dec, zero_dec, &result));
  ck_assert_int_eq(2, s21_sub(min_dec, max_dec, &result));
}
END_TEST

START_TEST(mul_test_0) {
  s21_decimal result = {0};

  ck_assert_int_eq(0, s21_mul(zero_dec, zero_dec, &result));
  ck_assert_int_eq(1, s21_mul(max_dec, max_dec, &result));
  ck_assert_int_eq(1, s21_mul(min_dec, min_dec, &result));

  ck_assert_int_eq(0, s21_mul(zero_dec, max_dec, &result));
  ck_assert_int_eq(0, s21_mul(zero_dec, min_dec, &result));

  ck_assert_int_eq(0, s21_mul(max_dec, zero_dec, &result));
  ck_assert_int_eq(2, s21_mul(max_dec, min_dec, &result));

  ck_assert_int_eq(0, s21_mul(min_dec, zero_dec, &result));
  ck_assert_int_eq(2, s21_mul(min_dec, max_dec, &result));
}
END_TEST

START_TEST(div_test_0) {
  s21_decimal result = {0};

  ck_assert_int_eq(3, s21_div(zero_dec, zero_dec, &result));
  ck_assert_int_eq(0, s21_div(max_dec, max_dec, &result));
  ck_assert_int_eq(0, s21_div(min_dec, min_dec, &result));

  ck_assert_int_eq(0, s21_div(zero_dec, max_dec, &result));
  ck_assert_int_eq(0, s21_div(zero_dec, min_dec, &result));

  ck_assert_int_eq(3, s21_div(max_dec, zero_dec, &result));
  ck_assert_int_eq(0, s21_div(max_dec, min_dec, &result));

  ck_assert_int_eq(3, s21_div(min_dec, zero_dec, &result));
  ck_assert_int_eq(0, s21_div(min_dec, max_dec, &result));
}
END_TEST

START_TEST(mod_test_0) {
  s21_decimal result = {0};

  ck_assert_int_eq(3, s21_mod(zero_dec, zero_dec, &result));
  ck_assert_int_eq(0, s21_mod(max_dec, max_dec, &result));
  ck_assert_int_eq(0, s21_mod(min_dec, min_dec, &result));

  ck_assert_int_eq(0, s21_mod(zero_dec, max_dec, &result));
  ck_assert_int_eq(0, s21_mod(zero_dec, min_dec, &result));

  ck_assert_int_eq(3, s21_mod(max_dec, zero_dec, &result));
  ck_assert_int_eq(0, s21_mod(max_dec, min_dec, &result));

  ck_assert_int_eq(3, s21_mod(min_dec, zero_dec, &result));
  ck_assert_int_eq(0, s21_mod(min_dec, max_dec, &result));
}
END_TEST

/*
 *  Rounding Min, Max and Zero decimal values
 */

START_TEST(add_test_round) {
  s21_decimal result = {0};
  s21_decimal number = {0};
  number.bytes[EXP] = 1;

  number.bytes[0] = 4;
  // Positive first arg
  ck_assert_int_eq(0, s21_add(max_dec, number, &result));
  for (int i = 0; i < 3; i++) {
    ck_assert_int_eq(max_dec.bits[i], result.bits[i]);
  }
  // Negative first arg
  ck_assert_int_eq(0, s21_add(min_dec, number, &result));
  for (int i = 0; i < 3; i++) {
    ck_assert_int_eq(max_dec.bits[i], result.bits[i]);
  }

  number.bytes[0] = 6;
  // Positive first arg, overflow
  ck_assert_int_eq(1, s21_add(max_dec, number, &result));

  // Negative first arg
  ck_assert_int_eq(0, s21_add(min_dec, number, &result));
  ck_assert_int_eq(min_dec.bits[0] - 1, result.bits[0]);
  for (int i = 1; i < 3; i++) {
    ck_assert_int_eq(max_dec.bits[i], result.bits[i]);
  }

  number.bytes[0] = 5;
  // Banking rounding
  ck_assert_int_eq(1, s21_add(max_dec, number, &result));

  ck_assert_int_eq(0, s21_add(min_dec, number, &result));
  ck_assert_int_eq(max_dec.bits[0] - 1, result.bits[0]);
  for (int i = 1; i < 3; i++) {
    ck_assert_int_eq(max_dec.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(sub_test_round) {
  s21_decimal result = {0};
  s21_decimal number = {0};
  number.bytes[EXP] = 1;

  number.bytes[0] = 4;
  // Positive first arg
  ck_assert_int_eq(0, s21_sub(max_dec, number, &result));
  for (int i = 0; i < 3; i++) {
    ck_assert_int_eq(max_dec.bits[i], result.bits[i]);
  }
  // Negative first arg
  ck_assert_int_eq(0, s21_sub(min_dec, number, &result));
  for (int i = 0; i < 3; i++) {
    ck_assert_int_eq(max_dec.bits[i], result.bits[i]);
  }

  number.bytes[0] = 6;
  // Positive first arg, overflow
  ck_assert_int_eq(0, s21_sub(max_dec, number, &result));
  ck_assert_int_eq(max_dec.bits[0] - 1, result.bits[0]);
  for (int i = 1; i < 3; i++) {
    ck_assert_int_eq(max_dec.bits[i], result.bits[i]);
  }
  // Negative first arg
  ck_assert_int_eq(2, s21_sub(min_dec, number, &result));

  number.bytes[0] = 5;
  // Banking rounding
  ck_assert_int_eq(0, s21_sub(max_dec, number, &result));

  ck_assert_int_eq(max_dec.bits[0] - 1, result.bits[0]);
  for (int i = 1; i < 3; i++) {
    ck_assert_int_eq(max_dec.bits[i], result.bits[i]);
  }

  ck_assert_int_eq(2, s21_sub(min_dec, number, &result));
}
END_TEST

/*
 *  Arithmetic with converters
 */

START_TEST(add_test_2) {
  for (int32_t i = -5; i < 5; i++) {
    for (int32_t j = -5; j < 5; j++) {
      s21_decimal result = {0};

      s21_decimal val_1 = {0};
      s21_decimal val_2 = {0};

      s21_from_int_to_decimal(i, &val_1);
      s21_from_int_to_decimal(j, &val_2);

      s21_add(val_1, val_2, &result);

      int32_t res_num = i + j;
      if (res_num < 0) {
        res_num *= -1;
        ck_assert_int_eq(NEGATIVE, result.bytes[SIGN]);
      }

      ck_assert_int_eq(res_num, result.bits[0]);
    }
  }
}
END_TEST

START_TEST(sub_test_2) {
  for (int32_t i = -5; i < 5; i++) {
    for (int32_t j = -5; j < 5; j++) {
      s21_decimal result = {0};

      s21_decimal val_1 = {0};
      s21_decimal val_2 = {0};

      s21_from_int_to_decimal(i, &val_1);
      s21_from_int_to_decimal(j, &val_2);

      s21_sub(val_1, val_2, &result);

      int32_t res_num = i - j;
      if (res_num < 0) {
        res_num *= -1;
        ck_assert_int_eq(NEGATIVE, result.bytes[SIGN]);
      }

      ck_assert_int_eq(res_num, result.bits[0]);
    }
  }
}
END_TEST

START_TEST(mul_test_2) {
  for (int32_t i = -5; i < 5; i++) {
    for (int32_t j = -5; j < 5; j++) {
      s21_decimal result = {0};

      s21_decimal val_1 = {0};
      s21_decimal val_2 = {0};

      s21_from_int_to_decimal(i, &val_1);
      s21_from_int_to_decimal(j, &val_2);

      s21_mul(val_1, val_2, &result);

      int32_t res_num = i * j;
      if (res_num < 0) {
        res_num *= -1;
        ck_assert_int_eq(NEGATIVE, result.bytes[SIGN]);
      }

      ck_assert_int_eq(res_num, result.bits[0]);
    }
  }
}
END_TEST

START_TEST(div_test_2) {
  for (int32_t i = -5; i < 5; i++) {
    for (int32_t j = -5; j < 5; j++) {
      s21_decimal result = {0};

      s21_decimal val_1 = {0};
      s21_decimal val_2 = {0};

      if (j == 0) {
        j++;
      }

      s21_from_int_to_decimal(i, &val_1);
      s21_from_int_to_decimal(j, &val_2);

      s21_div(val_1, val_2, &result);
      s21_truncate(result, &result);

      int32_t res_num = i / j;
      if (res_num < 0) {
        res_num *= -1;
        ck_assert_int_eq(NEGATIVE, result.bytes[SIGN]);
      }

      ck_assert_int_eq(res_num, result.bits[0]);
    }
  }
}
END_TEST

START_TEST(mod_test_2) {
  for (int32_t i = -5; i < 5; i++) {
    for (int32_t j = -5; j < 5; j++) {
      s21_decimal result = {0};

      s21_decimal val_1 = {0};
      s21_decimal val_2 = {0};

      if (j == 0) {
        j++;
      }

      s21_from_int_to_decimal(i, &val_1);
      s21_from_int_to_decimal(j, &val_2);

      s21_mod(val_1, val_2, &result);
      s21_truncate(result, &result);

      int32_t res_num = i % j;
      if (res_num < 0) {
        res_num *= -1;
        ck_assert_int_eq(NEGATIVE, result.bytes[SIGN]);
      }

      ck_assert_int_eq(res_num, result.bits[0]);
    }
  }
}
END_TEST

/*
 *  Arithmetic combined tests
 */

START_TEST(arithm_combined_test_0) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};

  value_1.bits[0] = UINT32_MAX;
  value_2.bits[0] = UINT32_MAX;

  ck_assert_int_eq(0, s21_add(value_1, value_2, &result));
  ck_assert_int_eq(0, s21_sub(result, value_2, &result));

  ck_assert_int_eq(1, s21_is_equal(value_2, result));
}
END_TEST

START_TEST(arithm_combined_test_1) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};

  value_1.bits[0] = UINT32_MAX / 3;
  value_2.bits[0] = UINT32_MAX / 5;

  value_1.bytes[EXP] = 13;
  value_2.bytes[EXP] = 24;

  ck_assert_int_eq(0, s21_add(value_1, value_2, &result));
  ck_assert_int_eq(0, s21_sub(result, value_1, &result));

  ck_assert_int_eq(1, s21_is_equal(value_2, result));
}
END_TEST

START_TEST(arithm_combined_test_2) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};

  value_1.bits[0] = 123;
  value_2.bits[0] = 2;

  ck_assert_int_eq(0, s21_mul(value_1, value_2, &value_2));
  ck_assert_int_eq(0, s21_sub(value_2, value_1, &result));

  ck_assert_int_eq(1, s21_is_equal(value_1, result));
}
END_TEST

START_TEST(arithm_combined_test_3) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal value_3 = {0};
  s21_decimal value_4 = {0};

  value_1.bits[0] = 15;
  value_2.bits[0] = 2;
  value_3.bits[0] = 3;
  value_4.bits[0] = 120;

  // ((15 * 2 + 15) * 3) % 120 = 15
  s21_mul(value_1, value_2, &value_2);
  s21_add(value_2, value_1, &value_2);
  s21_mul(value_2, value_3, &value_2);
  s21_mod(value_2, value_4, &value_2);

  ck_assert_int_eq(1, s21_is_equal(value_1, value_2));
}
END_TEST

/*
 *  Arithmetic combined with converters tests
 */

START_TEST(arithm_convert_combined_test_0) {
  for (int i = -5; i <= 5; i++) {
    s21_decimal value_1 = {0};
    s21_from_int_to_decimal(i, &value_1);
    value_1.bytes[EXP] = i * i;
    for (int j = -5; j <= 5; j++) {
      s21_decimal value_2 = {0};
      s21_decimal result = {0};
      s21_from_int_to_decimal(j, &value_2);
      value_2.bytes[EXP] = j * j;

      ck_assert_int_eq(0, s21_add(value_1, value_2, &result));
      ck_assert_int_eq(0, s21_sub(value_1, value_2, &result));
      ck_assert_int_eq(0, s21_mul(value_1, value_2, &result));

      if (j == 0) {
        ck_assert_int_eq(3, s21_div(value_1, value_2, &result));
        ck_assert_int_eq(3, s21_mod(value_1, value_2, &result));
      } else {
        ck_assert_int_eq(0, s21_div(value_1, value_2, &result));
        ck_assert_int_eq(0, s21_mod(value_1, value_2, &result));
      }
    }
  }
}
END_TEST

Suite *s21_arithmetic_tests(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_arithmetic_tests");
  tc = tcase_create("core");

  suite_add_tcase(s, tc);

  tcase_add_test(tc, add_test_0);
  tcase_add_test(tc, sub_test_0);
  tcase_add_test(tc, mul_test_0);
  tcase_add_test(tc, div_test_0);
  tcase_add_test(tc, mod_test_0);

  tcase_add_test(tc, add_test_round);
  tcase_add_test(tc, sub_test_round);

  tcase_add_test(tc, add_test_2);
  tcase_add_test(tc, sub_test_2);
  tcase_add_test(tc, mul_test_2);
  tcase_add_test(tc, div_test_2);
  tcase_add_test(tc, mod_test_2);

  tcase_add_test(tc, arithm_combined_test_0);
  tcase_add_test(tc, arithm_combined_test_1);
  tcase_add_test(tc, arithm_combined_test_2);
  tcase_add_test(tc, arithm_combined_test_3);

  tcase_add_test(tc, arithm_convert_combined_test_0);

  return s;
}