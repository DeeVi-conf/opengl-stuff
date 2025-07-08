CXX = g++
CXXFLAGS = -Wall -Wextra -Wpedantic -g -fsanitize=address,undefined -std=c++17 -Iinclude

LDFLAGS = -lglfw -ldl -lGL

SRC = src/test2.cpp glad/glad.c
OUT = bin/opengl-test

all: $(OUT)

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT) $(LDFLAGS)

clean:
	rm -f $(OUT)
