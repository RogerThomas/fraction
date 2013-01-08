CC=g++
CFLAGS=-O3 -Wall
MAIN=main.cpp
SOURCES=fraction.cpp
OBJECTS=$(SOURCES:.cpp=.o) $(MAIN:.cpp=.o)
TARGET=main

ALL: $(SOURCES) $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(CFLAGS) -o $@ 

$(TARGET): $(SOURCES)
$(OBJECTS): $(SOURCES:.cpp=.h)


.PHONY: clean
clean:
	rm -rf $(OBJECTS) $(TARGET)

