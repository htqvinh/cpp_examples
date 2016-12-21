
include declare.mk

CPPFLAGS = $(INCLUDE)	#for g++
#CFLAGS	= $(INCLUDE)	#for gcc

SOURCES = $(shell find $(SOURCEDIR) -name '*.cpp')
OBJECTS = $(patsubst %.cpp, %.o, $(SOURCES))

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@echo "--->>> Linking"
	ar -r $@ $(OBJECTS)

clean:
	rm -f $(TARGET)
	rm -f $(shell find $(SOURCEDIR) -name '*.o')