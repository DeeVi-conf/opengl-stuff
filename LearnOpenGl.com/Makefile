CXX = clang++
CXXFLAGS = -Wall -Wextra -Wpedantic -g -fsanitize=address,undefined -std=c++17 -Iinclude

LDFLAGS = -lglfw -ldl -lGL

SRC = src/exercises-2/exercise-2-2/main.cpp glad/glad.c
OUT = bin/exercise-2-2

all: $(OUT)

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT) $(LDFLAGS)

clean:
	rm -f $(OUT)
