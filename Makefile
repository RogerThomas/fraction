CC=g++
CFLAGS=-c -O3 -Wall
LDFLAGS=
TARGET=main
CLASSES=fraction.cpp
SOURCES= $(CLASSES) $(TARGET).cpp
OBJECTS=$(SOURCES:.cpp=.o)
CLASSOBJECTS=$(CLASSES:.cpp=.o)

all: $(SOURCES) $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@


$(TARGET).o: $(CLASSES:.cpp=.h) Makefile
$(CLASSOBJECTS): $(CLASSES:.cpp=.h) Makefile


.PHONY: clean
clean:
	rm -rf $(OBJECTS) $(TARGET) *.out *.dat

