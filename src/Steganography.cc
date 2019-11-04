#include <Steganography.h>

Steganography::Steganography(const char* filename) : filename(filename) {
  input.open(filename, std::ios::binary);
  input_size=calculate_input_size();
}

Steganography::~Steganography() {
  input.close();
}

size_t Steganography::calculate_input_size() {
  input.seekg(0, std::ios::end);
  size_t input_size = input.tellg();
  input.seekg(0, std::ios::beg);
  return input_size;
} 