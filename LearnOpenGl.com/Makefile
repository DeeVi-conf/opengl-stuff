CXX = clang++
CXXFLAGS = -Wall -Wextra -Wpedantic -g -Iinclude

LDFLAGS = -lglfw -ldl -lGL

SRC = src/colour.cpp glad/glad.c src/stb_image_impl.cpp 
OUT = bin/colour

all: $(OUT)

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT) $(LDFLAGS)

clean:
	rm -f $(OUT)
