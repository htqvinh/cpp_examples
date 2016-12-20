
include declare.mk

CPPFLAGS = -I./include/	#for g++
#CFLAGS	= -I./include/	#for gcc

SOURCES = $(shell find $(SOURCEDIR) -name '*.cpp')
OBJECTS = $(patsubst %.cpp, %.o, $(SOURCES))

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@echo "--->>> Linking" 
	$(CXX) -o $@ $(OBJECTS)

clean:
	rm -f $(TARGET)
	rm -f $(shell find $(SOURCEDIR) -name '*.o')