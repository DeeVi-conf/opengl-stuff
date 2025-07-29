CXX = clang++
CXXFLAGS = -Wall -Wextra -Wpedantic -g -Iinclude

LDFLAGS = -lglfw -ldl -lGL

SRC = src/Lighting_exercises/exercise-3/exercise-3.cpp glad/glad.c src/stb_image_impl.cpp 
OUT = bin/lighting-exercise-3

all: $(OUT)

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT) $(LDFLAGS)

clean:
	rm -f $(OUT)
