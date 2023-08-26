#pragma once

#include <string>

class Generator {
public:
  static const std::string filename;

  /**
   * @brief Generates data as s21_decimal in range from min to max
   *
   * @param min Minimal value
   * @param max Maximal value
   * @param count Number of values
   */
  static void GenerateData(int min, int max, int count);

private:
  Generator(){}; // Static class
};
