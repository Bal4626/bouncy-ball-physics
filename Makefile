CXX = g++
CXXFLAGS = -Iinclude -Wall -std=c++11
#LIBS2 = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
LIBS = $(shell pkg-config --libs raylib)

TARGET = build/main
SRC = src/main.cpp src/Ball.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(SRC) $(CXXFLAGS) $(LIBS) -o $(TARGET)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)