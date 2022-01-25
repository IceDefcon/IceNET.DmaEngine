
TARGET=dma
CC=g++
ASM=nasm 
AFLAGS=-f elf64
CFLAGS= -m64 -lpthread
ASM_OBJECTS=src/link.o

SRCS=\
    src/main.cpp \
    src/Dma.cpp

SRCS_ASM=\
	src/link.asm \

INCLUDES=\
    -Iinclude \

all: link.o Main

Main:
	$(CC) $(SRCS) $(CFLAGS) $(INCLUDES) $(ASM_OBJECTS) -o $(TARGET)

link.o: src/link.asm
	$(ASM) $(AFLAGS) $(SRCS_ASM)

clean:
	rm $(TARGET) $(ASM_OBJECTS)
