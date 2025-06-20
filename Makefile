CXX = g++
CXXFLAGS = -Wall -Wextra -Wpedantic -g -fsanitize=address,undefined -std=c++17
LDFLAGS = -lglfw -lGLEW -lGL -lm -ldl

SRC = test1.cpp
OBJ = $(SRC:.c=.o)
OUT = openGL-test-program

all: $(OUT)

$(OUT): $(OBJ)
	$(CXX) $(OBJ) -o $(OUT) $(LDFLAGS)

%.o: %.c
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(OUT)

