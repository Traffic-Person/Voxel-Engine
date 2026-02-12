CXX = g++
CXXFLAGS = -std=c++17 -Wall
LDFLAGS = -lSDL2

TARGET = voxel

SRC = main.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

clean:
	rm -rf $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
