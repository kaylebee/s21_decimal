#pragma once

#include <fstream>
#include <string>

/**
 * @brief Instance works with data in "data" folder
 * (if folder doesn't exist, creates one)
 */
class FileHandler {
private:
  const std::string dir = "data";

public:
  FileHandler();

  std::fstream OpenRead(std::string filename);
  std::fstream OpenWrite(std::string filename);
};