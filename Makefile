CXX = g++
CXXFLAGS = -Wall -std=c++11
LIBS = -Iinclude -Wall -std=c++11 -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

TARGET = build/main
SRC = src/main.cpp src/Ball.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(SRC) $(CXXFLAGS) $(LIBS) -o $(TARGET)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)