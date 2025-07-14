#ifndef FILE_H
#define FILE_H

#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <unistd.h>

inline std::string ShaderOpen(const std::string &Path) {
  std::string Code;
  std::ifstream ShaderFile;
  ShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  try {
    std::cout<<"Opening File "<<Path<<"\n";
    ShaderFile.open(Path);
    std::cout << "File Oppened."<<std::endl;

    std::stringstream ShaderStream;
    ShaderStream << ShaderFile.rdbuf();
    std::cout << "rdbuff done\n";

    ShaderFile.close();
    Code = ShaderStream.str();
  } catch (std::ifstream::failure &e) {
    std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what()
              << std::endl;
  }

  return {Code};
}

#endif
