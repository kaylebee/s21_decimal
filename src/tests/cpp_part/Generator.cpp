#include "Generator.h"

#include <stdlib.h>
#include <time.h>

#include "FileHandler.h"
#include "s21_decimal.h"

const std::string Generator::filename = "input_values.dat";

void Generator::GenerateData(int min, int max, int count) {
  auto file_handler = FileHandler{};
  int offset = min, range = max - min;
  s21_decimal decimal;
  int value;

  srand(time(NULL));
  auto file = file_handler.OpenWrite(Generator::filename);

  file.seekg(0, std::ios::beg);
  file.write((char *)&count, sizeof(int));

  for (int i = 0; i < count; i++) {
    value = offset + rand() % range;
    s21_from_int_to_decimal(value, &decimal);
    file.write((char *)&decimal, sizeof(s21_decimal));
  }

  file.close();
}
