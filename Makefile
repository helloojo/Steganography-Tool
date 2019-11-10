all:

pre-build: 
	mkdir -p obj

src_path=./src/
include_path=./include/
obj_path=./obj/

%.o: .$(src_path)%.cc
	g++ -c -O2 -Wall -I $(include_path) -o $@ -Wextra -pedantic $<

HEADERS_OBJS = $(obj_path)Steganography.o \
								$(obj_path)JPG_Steganography.o \
  		 					$(obj_path)BMP_Steganography.o \
								$(obj_path)PNG_Steganography.o
HEADERS = $(include_path)Steganography.h \
					$(include_path)BMP_Steganography.h \
					$(include_path)JPG_Steganography.h \
					$(include_path)PNG_Steganography.h
TARGET = steg
TARGET_OBJ = $(obj_path)main.o

library: $(HEADERS_OBJS)

$(HEADERS_OBJS): $(HEADERS)

$(TARGET_OBJ): $(HEADERS)

$(TARGET) : $(TARGET_OBJ) $(HEADERS_OBJS)
	g++ $^ -o $@

all: pre-build library $(TARGET)