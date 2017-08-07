include declare.mk

BUILD_TYPE = $(TYPE)$(BITS)

DBUG = 
ifeq ($(TYPE), Debug)
DBUG = -g
endif

TARGET = $(BUILD_TYPE)/$(NAME)
COMP   = $(COMPILER) -m$(BITS) -o
ifeq ($(IS_LIB), true)
TARGET = $(BUILD_TYPE)/lib$(NAME).a
COMP   = ar -r
endif

CC  = gcc -m$(BITS) $(DBUG) $(FLAGS) $(DEFINES) $(INCLUDE)
CXX = g++ -m$(BITS) $(DBUG) $(FLAGS) $(DEFINES) $(INCLUDE)

SOURCES = \
	$(shell find $(SOURCEDIR) -name '*.c*')

OBJECTS = \
	$(filter %o, \
		$(patsubst %.cpp, $(BUILD_TYPE)/%.o, $(SOURCES)) \
		$(patsubst %.c, $(BUILD_TYPE)/%.o, $(SOURCES)) \
	)

#-----------------------------------------------------------------------
all: buildrepo $(TARGET)

$(BUILD_TYPE): buildrepo $(TARGET)

$(TARGET): $(OBJECTS)
	$(COMP) $@ $(OBJECTS) $(LIBS)

$(BUILD_TYPE)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) -c -o $@ $<

$(BUILD_TYPE)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) -c -o $@ $<
	
.PHONY: clean clean-all
clean:
	rm -rf $(BUILD_TYPE)

clean-all:
	rm -rf Debug32 Debug64
	rm -rf Release32 Release64

#-----------------------------------------------------------------------
buildrepo:
	@$(call make-depend)