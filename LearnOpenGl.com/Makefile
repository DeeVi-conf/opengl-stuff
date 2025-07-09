CXX = clang++
CXXFLAGS = -Wall -Wextra -Wpedantic -g -fsanitize=address,undefined -std=c++17 -Iinclude

LDFLAGS = -lglfw -ldl -lGL

SRC = src/exercises-1/exercise-1-1.cpp glad/glad.c
OUT = bin/exercise-1-1

all: $(OUT)

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT) $(LDFLAGS)

clean:
	rm -f $(OUT)
