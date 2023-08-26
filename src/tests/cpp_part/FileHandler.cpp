#include "FileHandler.h"

#include <filesystem>

FileHandler::FileHandler() {
  bool is_dir_exists = std::filesystem::exists(this->dir);

  if (!is_dir_exists) {
    std::filesystem::create_directory(this->dir);
  }
}

std::fstream FileHandler::OpenRead(std::string filename) {
  std::fstream in;

  std::string path = this->dir + "/" + filename;
  in.open(path, std::ios::in | std::ios::binary);

  return in;
}

std::fstream FileHandler::OpenWrite(std::string filename) {
  std::fstream out;

  std::string path = this->dir + "/" + filename;
  out.open(path, std::ios::out | std::ios::binary);

  return out;
}
