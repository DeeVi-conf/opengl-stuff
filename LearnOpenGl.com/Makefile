# The entire directory structure of this thing is increadibly f*cked.
# I don't have the time to fix it.
# Machine spirit help me.

CXX = clang++
CXXFLAGS = -Wall -Wextra -Wpedantic -g -Iinclude

LDFLAGS = -lglfw -ldl -lGL

SRC = src/materials.cpp glad/glad.c src/stb_image_impl.cpp 
OUT = bin/materials

all: $(OUT)

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT) $(LDFLAGS)

clean:
	rm -f $(OUT)
