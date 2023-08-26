#include "Test.h"

int (*Test::arithm_operators[5])(s21_decimal, s21_decimal, s21_decimal *) = {
    s21_add, s21_sub, s21_mul, s21_div, s21_mod};

int (*Test::cmp_operators[6])(s21_decimal, s21_decimal) = {
    s21_is_less,  s21_is_less_or_equal, s21_is_greater, s21_is_greater_or_equal,
    s21_is_equal, s21_is_not_equal};

int (*Test::other_operators[4])(s21_decimal, s21_decimal *) = {
    s21_negate, s21_floor, s21_truncate, s21_round};

void Test::Start() {
  auto file_handler = FileHandler{};
  std::fstream in = file_handler.OpenRead(Generator::filename);

  ArithmTest(in, file_handler);
  CmpTest(in, file_handler);
  OtherTest(in, file_handler);

  in.close();
}

void Test::ArithmTest(std::fstream &in, FileHandler file_handler) {
  auto out = file_handler.OpenWrite("arithm_results.dat");

  s21_decimal value1, value2, result;
  for (int i = 0; i < 5; i++) {
    int count;
    in.seekg(0, std::ios::beg);
    in.read((char *)&count, sizeof(int));

    for (int j = 0; j < count; j += 2) {
      in.read((char *)&value1, sizeof(s21_decimal));
      in.read((char *)&value2, sizeof(s21_decimal));
      arithm_operators[i](value1, value2, &result);
      out.write((char *)&result, sizeof(s21_decimal));
    }
  }

  out.close();
}

void Test::CmpTest(std::fstream &in, FileHandler file_handler) {
  auto out = file_handler.OpenWrite("cmp_results.dat");

  s21_decimal value1, value2;
  int result;
  for (int i = 0; i < 6; i++) {
    int count;
    in.seekg(0, std::ios::beg);
    in.read((char *)&count, sizeof(int));

    for (int j = 0; j < count; j += 2) {
      in.read((char *)&value1, sizeof(s21_decimal));
      in.read((char *)&value2, sizeof(s21_decimal));
      result = cmp_operators[i](value1, value2);
      out.write((char *)&result, sizeof(int));
    }
  }

  out.close();
}

void Test::OtherTest(std::fstream &in, FileHandler file_handler) {
  auto out = file_handler.OpenWrite("other_results.dat");

  s21_decimal value, result;
  for (int i = 0; i < 4; i++) {
    int count;
    in.seekg(0, std::ios::beg);
    in.read((char *)&count, sizeof(int));

    for (int j = 0; j < count; j++) {
      in.read((char *)&value, sizeof(s21_decimal));
      other_operators[i](value, &result);
      out.write((char *)&result, sizeof(s21_decimal));
    }
  }

  out.close();
}
