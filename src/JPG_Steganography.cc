#include <JPG_Steganography.h>
#include <cstring>

JpgSteganography::JpgSteganography(const char* filename)
    : Steganography(filename) {
}

bool JpgSteganography::Hide(const char* message, const char* output_filename) {
  output.open(output_filename, std::ios::binary);
  size_t msg_len = strlen(message);

  unsigned char data;
  for (size_t i = 0; i < input_size; i++) {
    data = input.get();
    output << data;
  }

  output << message;
  output.write((const char*)&msg_len, sizeof(msg_len));
  output.close();
  return true;
}

std::string JpgSteganography::Reveal() {
  std::string message = "";

  unsigned short EOI;
  input.seekg(-2, std::ios::end);
  input.read((char*)&EOI, sizeof(EOI));
  if (EOI == 0xD9FF) {
    return message;
  }

  size_t msg_len = 0;
  input.seekg(-static_cast<int>(sizeof(msg_len)), std::ios::end);
  input.read((char*)&msg_len, sizeof(msg_len));

  input.seekg(-static_cast<int>(sizeof(msg_len) + msg_len), std::ios::end);
  char data;
  for (size_t i = 0; i < msg_len; i++) {
    data = input.get();
    message.push_back(data);
  }
  return message;
}