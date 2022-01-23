
TARGET=app
CC=g++
ASM=nasm -f elf64
CFLAGS= -m64
OBJECTS= link.o

SRCS=\
    src/main.cpp \

INCLUDES=\
    -Iinclude \

all:  link.asm
	$(ASM) link.asm
	$(CC) $(INCLUDES) $(SRCS) $(CFLAGS) $(OBJECTS) -o $(TARGET)

clean:
	rm app link.o
