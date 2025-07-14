CXX = clang++
CXXFLAGS = -Wall -Wextra -Wpedantic -g -fsanitize=address,undefined -Iinclude

LDFLAGS = -lglfw -ldl -lGL

SRC = src/texture.cpp glad/glad.c src/stb_image_impl.cpp
OUT = bin/texture

all: $(OUT)

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT) $(LDFLAGS)

clean:
	rm -f $(OUT)
