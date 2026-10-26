# Makefile du projet "Nourrir les pigeons"
# Utilisation :  make        -> compile
#                make run    -> compile et lance
#                make clean  -> supprime les fichiers compilés

CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2 -Isrc
TARGET   := pigeons

# Tous les .cpp du dossier src sont compilés automatiquement :
# quand vous ajoutez Pigeon.cpp ou Scene.cpp, rien à changer ici.
SRCS := $(wildcard src/*.cpp)
OBJS := $(SRCS:src/%.cpp=build/%.o)

# Bibliothèques selon le système
UNAME := $(shell uname -s 2>/dev/null)
ifeq ($(OS),Windows_NT)
    # Windows avec MinGW (raylib installé dans C:/raylib par l'installeur officiel)
    CXXFLAGS += -IC:/raylib/raylib/src
    LDLIBS   := -LC:/raylib/raylib/src -lraylib -lopengl32 -lgdi32 -lwinmm -lpthread
    TARGET   := pigeons.exe
else ifeq ($(UNAME),Darwin)
    # macOS avec Homebrew : brew install raylib
    CXXFLAGS += $(shell pkg-config --cflags raylib 2>/dev/null)
    LDLIBS   := $(shell pkg-config --libs raylib 2>/dev/null || echo -lraylib) \
                -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
else
    # Linux
    LDLIBS := -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
endif

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDLIBS)

build/%.o: src/%.cpp | build
	$(CXX) $(CXXFLAGS) -c $< -o $@

build:
	mkdir -p build

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf build $(TARGET) pigeons.exe

.PHONY: all run clean
