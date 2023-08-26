#pragma once

#include <fstream>
#include <string>

#include "FileHandler.h"
#include "Generator.h"
#include "s21_decimal.h"

class Test {
public:
  /**
   * @brief Prints results of s21_decimal functions work
   */
  static void Start();

private:
  Test(){}; // static class

  static int (*arithm_operators[5])(s21_decimal, s21_decimal, s21_decimal *);
  static int (*cmp_operators[6])(s21_decimal, s21_decimal);
  static int (*other_operators[4])(s21_decimal, s21_decimal *);

  static void ArithmTest(std::fstream &in, FileHandler file_handler);
  static void CmpTest(std::fstream &in, FileHandler file_handler);
  static void OtherTest(std::fstream &in, FileHandler file_handler);
};
