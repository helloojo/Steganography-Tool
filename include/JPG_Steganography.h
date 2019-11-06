#ifndef JPG_STEGANOGRAPHY_HH
#define JPG_STEGANOGRAPHY_HH
#include <Steganography.h>

class JpgSteganography : public Steganography {
public:
  JpgSteganography(const char* filename);
  bool Hide(const char* message, const char* output_filename);
  std::string Reveal();
};

#endif