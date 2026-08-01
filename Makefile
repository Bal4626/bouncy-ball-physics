CXX = g++
CXXFLAGS = -Wall -std=c++11
LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

TARGET = main
SRC = main.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(SRC) $(CXXFLAGS) $(LIBS) -o $(TARGET)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)