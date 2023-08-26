#include "s21_tests.h"

SRunner *default_srunner_create() {
  SRunner *sr;

  sr = srunner_create(s21_arithmetic_tests());
  srunner_add_suite(sr, s21_comparison_tests());
  srunner_add_suite(sr, s21_other_functions_tests());
  srunner_add_suite(sr, s21_converters_tests());

  return sr;
}

int main(void) {
  int exit_status = 1;
  int number_failed = 0;
  SRunner *sr = NULL;

  sr = default_srunner_create();

  srunner_set_log(sr, "test.log");
  srunner_run_all(sr, CK_NORMAL);

  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  if (number_failed == 0) {
    exit_status = 0;
  }

  return exit_status;
}