CC=g++
CFLAGS=-c -O3 -Wall
TARGET=main
CLASSES=fraction.cpp
SOURCES= $(CLASSES) $(TARGET).cpp
OBJECTS=$(SOURCES:.cpp=.o)
CLASSOBJECTS=$(CLASSES:.cpp=.o)

all: $(SOURCES) $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ 

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@


$(TARGET).o: Makefile
$(CLASSOBJECTS): $(CLASSES:.cpp=.h) Makefile


.PHONY: clean
clean:
	rm -rf $(OBJECTS) $(TARGET)

