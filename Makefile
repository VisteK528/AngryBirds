# Makefile for SFML/BOX2D projects
# Made by Piotr Patek

# -- Compiler --
CXX = g++
CXX_VERSION = c++2a
CXX_FLAGS = -std=$(CXX_VERSION) -g -Wall -Wextra
OS := $(shell uname)

# Linux version
LINUX_INCLUDES = -I/usr/include/SFML -Ibox2d/include
LINUX_LIBS = -L box2d/build/bin -l:libbox2d.a -L/usr/lib/x86_64-linux-gnu -lsfml-graphics -lsfml-window -lsfml-system

# MacOS version
MACOS_INCUDES = -I/opt/homebrew/Cellar/sfml/2.5.1_2/include -Ibox2d/include
MACOS_LIBS = -Lbox2d/build/bin box2d/build/bin/libbox2d.a -L/opt/homebrew/Cellar/sfml/2.5.1_2/lib -lsfml-graphics -lsfml-window -lsfml-system

SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system
SFML_LIBS_PATH = /usr/lib/x86_64-linux-gnu

# Choose paths depending on operating system
ifeq ($(OS), Darwin)
	INCLUDES = $(MACOS_INCUDES)
	LIBS = $(MACOS_LIBS)
else
	INCLUDES = $(LINUX_INCLUDES)
	LIBS = $(LINUX_LIBS)
endif

SRC = ${wildcard src/*.cpp src/states/*.cpp src/entities/*.cpp src/entities/birds/*.cpp}

# -- Targets --
all:
	@echo "* Building main *"
	$(CXX) $(CXX_FLAGS) $(INCLUDES) $(SRC) main.cpp -o build/main $(LIBS)

clean:
	rm -f build/main build/*.o
