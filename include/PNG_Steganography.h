#ifndef PNG_STEGANOGRAPHY_H
#define PNG_STEGANOGRAPHY_H
#include <Steganography.h>

class PNG_Steganography : public Steganography {
 public:
  PNG_Steganography(const char* filename);
  bool Hide(const char* message, const char* output_filename);
  std::string Reveal();
};

#endif