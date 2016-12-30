
include declare.mk

CPPFLAGS = $(FLAGS) $(INCLUDE)	#for g++
#CFLAGS	= $(FLAGS) $(INCLUDE)	#for gcc

SOURCES = $(shell find $(SOURCEDIR) -name '*.cpp')
OBJECTS = $(patsubst %.cpp, %.o, $(SOURCES))

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@echo "--->>> Linking"
	ar -r $@ $(OBJECTS)

clean:
	rm -f $(TARGET)
	rm -f $(shell find $(SOURCEDIR) -name '*.o')