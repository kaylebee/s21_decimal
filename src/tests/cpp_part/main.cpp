#include <iostream>

#include "FileHandler.h"
#include "Generator.h"
#include "Test.h"
#include "s21_decimal.h"

int main(void) {
  Generator::GenerateData(-1000000, 1000000, 10000);
  Test::Start();
  return 0;
}
