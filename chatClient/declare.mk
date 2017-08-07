# editable
IS_LIB     = false
NAME       = ChatClient
COMPILER   = g++
FLAGS      = -std=c++11
TYPE       = Debug
BITS       = 64

# use for commandline
ifeq ($(MAKECMDGOALS), Debug64)
  TYPE = Debug
  BITS = 64
endif
ifeq ($(MAKECMDGOALS), Debug32)
  TYPE = Debug
  BITS = 32
endif
ifeq ($(MAKECMDGOALS), Release64)
  TYPE = Release
  BITS = 64
endif
ifeq ($(MAKECMDGOALS), Release32)
  TYPE = Release
  BITS = 32
endif
# end

BUILD_TYPE = $(TYPE)$(BITS)

define make-depend
endef

DEFINES		= \

SOURCEDIR   = \
	source

INCLUDE 	= \
	-I./include \
	-I../vnet/include \
	-I../vlog/include \
	-I../vutil/include \
	-I../chatGen/include \

LIBS		= \
	-L../vnet/$(BUILD_TYPE) -lVnet \
	-L../vlog/$(BUILD_TYPE) -lVlog \
	-L../vutil/$(BUILD_TYPE) -lVutil \
	-L../chatGen/$(BUILD_TYPE) -lChatGen \
	-lpthread -static-libstdc++ \
