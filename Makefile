# OSFLAG :=
# ifeq ($(OS),Windows_NT)
# 	OSFLAG += -D WIN32
# 	ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
# 		OSFLAG += -D AMD64
# 	endif
# 	ifeq ($(PROCESSOR_ARCHITECTURE),x86)
# 		OSFLAG += -D IA32
# 	endif
# else
# 	UNAME_S := $(shell uname -s)
# 	ifeq ($(UNAME_S),Linux)
# 		OSFLAG += -D LINUX
# 	endif
# 	ifeq ($(UNAME_S),Darwin)
# 		OSFLAG += -D OSX
# 	endif
# 		UNAME_P := $(shell uname -p)
# 	ifeq ($(UNAME_P),x86_64)
# 		OSFLAG += -D AMD64
# 	endif
# 		ifneq ($(filter %86,$(UNAME_P)),)
# 	OSFLAG += -D IA32
# 		endif
# 	ifneq ($(filter arm%,$(UNAME_P)),)
# 		OSFLAG += -D ARM
# 	endif
# endif

CC = gcc
RM = rm -rf
MKDIR = mkdir -p

SRC = src
OBJ = obj
BIN = bin
INC = include

CCFLAGS = -I $(INC) -O2
LDFLAGS = -l SDL2 -l SDL2_image
CXXFLAGS = $(CCFLAGS) $(LDFLAGS) -fPIC

SOURCES = $(wildcard $(SRC)/*.c)
OBJECTS = $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SOURCES))
TARGET = $(BIN)/ClockworkIsland

$(OBJ):
	$(MKDIR) $@

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) -c -o $@ $< $(CCFLAGS) -Wall

.PHONY: all
all: clean $(OBJ) $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS) $(CXXFLAGS)

.PHONY: clean
clean:
	$(RM) $(OBJ) $(TARGET)