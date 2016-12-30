# editable
TARGET 		= ChatClient
SOURCEDIR 	= source
FLAGS 		= -g -std=c++11

INCLUDE 	= -I./include \
	-I/data/proj/cpp_examples/vnet/include \
	-I/data/proj/cpp_examples/vlog/include \
	-I/data/proj/cpp_examples/vutil/include \
	-I/data/proj/cpp_examples/chatGen/include \
	
LIB 		= -lpthread -static-libstdc++ \
	-L/data/proj/cpp_examples/vnet -lVnet \
	-L/data/proj/cpp_examples/vlog -lVlog \
	-L/data/proj/cpp_examples/vutil -lVutil \
	-L/data/proj/cpp_examples/chatGen -lChatGen \
#
