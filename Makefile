CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -pedantic

TARGET := runwayRush
OBJECTS := runwayRush.o

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET)

runwayRush.o: runwayRush.cpp
	$(CXX) $(CXXFLAGS) -c runwayRush.cpp -o runwayRush.o

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJECTS) map.txt