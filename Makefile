CXX = g++
CXXFLAGS = -std=c++17 -g -Iinclude
SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)
TARGET = "app.exe"

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	@if exist $(TARGET) del /Q $(TARGET)