TARGET = servo
OBJECTS = $(TARGET).o

$(TARGET):$(OBJECTS)
	g++ -o $(TARGET) $(OBJECTS)
$(OBJECTS):$(TARGET).cpp
	g++ -c $(TARGET).cpp
install:
	cp $(TARGET) /usr/local/bin/$(TARGET)
clean:
	rm -f *.o $(TARGET)
