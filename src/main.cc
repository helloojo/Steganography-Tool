#include <BMP_Steganography.h>
#include <JPG_Steganography.h>
#include <Steganography.h>
#include <cstring>
#include <iostream>

#ifndef WIN32
using strcmpi = strcasecmp;
#endif

enum { ERROR = -1, HIDE, REVEAL };
enum { NOTYPE = -1, JPEG, BMP, PNG };

static const char* filename;
static const char* message;
static const char* outputfile;

const char* usage();
const char* type_error();
void print_error_message(const char* msg);
int tokenize_argv(int argc, const char* argv[]);
int check_file_type(const char* filename);

int main(int argc, const char* argv[]) {
  int argv_token = tokenize_argv(argc, argv);
  if (argv_token == ERROR) {
    print_error_message(usage());
    return 1;
  }

  int file_type = check_file_type(filename);
  if (file_type == NOTYPE) {
    print_error_message(type_error());
    return 1;
  }

  Steganography* steg = nullptr;
  switch (file_type) {
    case JPEG:
      steg = new JpgSteganography(filename);
      break;
    case BMP:
      steg = new BmpSteganography(filename);
      break;
  }

  switch (argv_token) {
    case HIDE:
      steg->Hide(message, outputfile);
      break;
    case REVEAL:
      std::cout << steg->Reveal() << std::endl;
      break;
  }
  if (steg != nullptr) {
    delete steg;
  }
  return 0;
}

const char* usage() {
  return "Usage: steg [-h filename \"message\" outputfile] [-r "
         "filename]\n";
}

const char* type_error() {
  return "Filetype: *.jp(e)g, *.png, *.bmp\n";
}

void print_error_message(const char* msg) {
  std::cerr << msg;
}

int tokenize_argv(int argc, const char* argv[]) {
  if (argc < 2 || argc > 5) {
    return ERROR;
  }
  size_t option_len = strlen(argv[1]);
  if (option_len != 2) {
    return ERROR;
  }
  switch (argv[1][1]) {
    case 'h':
      if (argc != 5) {
        return ERROR;
      }
      filename = argv[2];
      message = argv[3];
      outputfile = argv[4];
      return HIDE;
    case 'r':
      if (argc != 3) {
        return ERROR;
      }
      filename = argv[2];
      return REVEAL;
  }
  return ERROR;
}

int check_file_type(const char* filename) {
  while (*filename != '.' && *filename != '\0') {
    filename++;
  }
  if (*filename == '\0') {
    return NOTYPE;
  }
  if (strcmpi(filename, ".jpg") == 0 || strcmpi(filename, ".jpeg") == 0) {
    return JPEG;
  } else if (strcmpi(filename, ".bmp") == 0) {
    return BMP;
  } else if (strcmpi(filename, ".png") == 0) {
    return PNG;
  }
  return NOTYPE;
}