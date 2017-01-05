# editable
TARGET 		= test
SOURCEDIR 	= source
FLAGS 		= -g -std=c++11

INCLUDE 	= \
	-I./include \
	-I../vnet/include \
	-I../vlog/include \
	-I../vutil/include \
	-I../chatGen/include \

LIB 		= \
	-L../vnet -lVnet \
	-L../vlog -lVlog \
	-L../vutil -lVutil \
	-L../chatGen -lChatGen \
	-lpthread -static-libstdc++ \
