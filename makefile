CXX = gcc
SRC = ./src
MAIN = main.cpp
CXXFLAGS = -Wall -o
INCLUDE = $(SRC)/include
ifeq ($(OS), Windows_NT)
	LDFLAGS = lib/win -lstdc++ -lwx_baseu -lm
else
	LDFLAGS = lib/unix -lstdc++ -lwx_baseu -lm
endif
ifeq ($(OS), Windows_NT)
	TARGET = main.exe
else
	TARGET = main
endif
ifeq ($(OS), Windows_NT)
	RM = rmdir /S /Q
else
	RM = rm -rf
endif

.PHONY: build clean run test

all:
	$(MAKE) -si clean
	$(MAKE) -s build
	$(MAKE) -s run

test:
	$(MAKE) -si clean
	$(MAKE) -s build SRC=./test
	$(MAKE) -s run

build:
	mkdir build
	$(CXX) $(CXXFLAGS) ./build/$(TARGET) $(SRC)/$(MAIN) -I$(INCLUDE) -L$(LDFLAGS)

clean:
	$(RM) build

run:
	./build/$(TARGET)