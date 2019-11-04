#include <BMP_Steganography.h>
#include <Steganography.h>
#include <cstring>
#include <iostream>

enum { ERROR = -1, HIDE, REVEAL };

static const char* filename;
static const char* message;
static const char* outputfile;

int tokenize_argv(int argc, const char* argv[]);

int main(int argc, const char* argv[]) {
  int argv_token = tokenize_argv(argc, argv);
  if (argv_token == -1) {
    return 1;
  }
  Steganography* steg = new BmpSteganography(filename);
  switch (argv_token) {
    case HIDE:
      steg->Hide(message, outputfile);
      break;
    case REVEAL:
      std::cout << steg->Reveal() << std::endl;
      break;
  }
  delete steg;
  return 0;
}

int tokenize_argv(int argc, const char* argv[]) {
  if (argc < 2 || argc > 5) {
    std::cerr << "Usage: steg [-h filename \"message\" outputfile] [-r "
                 "filename]\n";
    return ERROR;
  }
  size_t option_len = strlen(argv[1]);
  if (option_len != 2) {
    std::cerr << "Usage: steg [-h filename \"message\" outputfile] [-r "
                 "filename]\n";
    return ERROR;
  }
  switch (argv[1][1]) {
    case 'h':
      if (argc != 5) {
        std::cerr << "Usage: steg [-h filename \"message\" outputfile] [-r "
                     "filename]\n";
        return ERROR;
      }
      filename = argv[2];
      message = argv[3];
      outputfile = argv[4];
      return HIDE;
    case 'r':
      if (argc != 3) {
        std::cerr << "Usage: steg [-h filename \"message\" outputfile] [-r "
                     "filename]\n";
        return ERROR;
      }
      filename = argv[2];
      return REVEAL;
  }
  return ERROR;
}