
TARGET=dma
CC=g++
ASM=nasm 
AFLAGS=-f elf64
CFLAGS= -m64 -lpthread
ASM_OBJECTS=src/Link.o

SRCS=\
    src/Main.cpp \
    src/Dma.cpp

SRCS_ASM=\
	src/Link.asm \

INCLUDES=\
    -Iinclude \

all: Link Main

Main:
	$(CC) $(SRCS) $(CFLAGS) $(INCLUDES) $(ASM_OBJECTS) -o $(TARGET)

Link:
	$(ASM) $(AFLAGS) $(SRCS_ASM)

clean:
	rm $(TARGET) $(ASM_OBJECTS)
