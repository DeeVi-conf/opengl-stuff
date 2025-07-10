CXX = clang++
CXXFLAGS = -Wall -Wextra -Wpedantic -g -fsanitize=address,undefined -std=c++17 -Iinclude

LDFLAGS = -lglfw -ldl -lGL

SRC = src/shaders-learn/shaders-learn.cpp glad/glad.c
OUT = bin/shaders-learn-bin

all: $(OUT)

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT) $(LDFLAGS)

clean:
	rm -f $(OUT)
