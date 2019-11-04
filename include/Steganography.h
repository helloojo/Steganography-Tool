#ifndef STEGANOGRAPHY_H
#define STEGANOGRAPHY_H
#include <fstream>
#include <string>

class Steganography {
 public:
  Steganography(const char* filename);
  virtual ~Steganography();
  virtual bool Hide(const char* message, const char* output_filename)=0;
  virtual std::string Reveal()=0;
 protected:
  const char* filename;
  std::ifstream input;
  std::ofstream output;
  size_t input_size;
  size_t calculate_input_size();
};

#endif