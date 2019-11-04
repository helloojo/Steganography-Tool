#ifndef BMP_STEGANOGRAPHY_H
#define BMP_STEGANOGRAPHY_H
#include <Steganography.h>

class BmpSteganography : public Steganography {
public:
  BmpSteganography(const char* filename);
  bool Hide(const char* message, const char* output_filename);
  std::string Reveal();
};

#endif