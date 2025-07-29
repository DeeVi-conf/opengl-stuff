CXX = clang++
CXXFLAGS = -Wall -Wextra -Wpedantic -g -Iinclude

LDFLAGS = -lglfw -ldl -lGL

SRC = src/Lighting_exercises/exercise-1/exercise-1.cpp glad/glad.c src/stb_image_impl.cpp 
OUT = bin/lighting-exercise-1

all: $(OUT)

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT) $(LDFLAGS)

clean:
	rm -f $(OUT)
