#include <BMP_Steganography.h>
#include <cstring>

BmpSteganography::BmpSteganography(const char* filename)
    : Steganography(filename) {
}

bool BmpSteganography::Hide(const char* message, const char* output_filename) {
  char* buf = new char[input_size];
  input.read(buf, input_size);
  size_t start_offset;
  memcpy(&start_offset, buf + 10, sizeof(start_offset));

  output.open(output_filename, std::ios::binary);

  size_t file_idx = start_offset;
  size_t msg_len = strlen(message);

  // //메시지 길이 삽입
  memcpy(buf + 6, &msg_len, sizeof(msg_len));

  for (size_t i = 0; i < start_offset; i++) {
    output << buf[i];
  }


  //메시지 삽입
  unsigned char onebit = 0b00000001;
  unsigned char zerobit = 0b11111110;
  size_t bitidx = 0;

  for (size_t i = 0; i < msg_len; i++) {
    for (int j = 7; j >= 0; j--) {
      if (message[i] & (1 << j)) {
        buf[file_idx] |= onebit;
      } else {
        buf[file_idx] &= zerobit;
      }
      output << buf[file_idx++];
      if (file_idx == input_size) {
        bitidx++;
        onebit = (1 << bitidx);
        zerobit = ~(1 << bitidx);
        file_idx = start_offset + 32;
      }
    }
  }

  //나머지 파일 처리
  for (; file_idx < input_size; file_idx++) {
    output << buf[file_idx];
  }

  delete[] buf;
  output.close();
  return true;
}

std::string BmpSteganography::Reveal() {
  std::string message;
  char* buf = new char[input_size];
  input.read(buf, input_size);
  size_t start_offset;
  memcpy(&start_offset, buf + 10, sizeof(start_offset));

  size_t file_idx = start_offset;
  size_t msg_len = 0;
  //메시지 길이 읽기
  memcpy(&msg_len, buf + 6, sizeof(msg_len));


  unsigned char onebit = 0b00000001;
  size_t bitidx = 0;

  for (size_t msg_idx = 0; msg_idx < msg_len; msg_idx++) {
    char msg_char = 0;
    for (int j = 0; j < 8; j++) {
      msg_char <<= 1;
      msg_char |= ((buf[file_idx++] & onebit) >> bitidx);
      if (file_idx == input_size) {
        file_idx = start_offset + 32;
        bitidx++;
      }
    }
    message.push_back(msg_char);
  }

  delete[] buf;
  return message;
}