# editable
TARGET 		= ChatServer
SOURCEDIR 	= source
FLAGS 		= -g -std=c++11

INCLUDE 	= -I./include \
	-I/data/proj/cpp_examples/vnet/include \
	-I/data/proj/cpp_examples/vlog/include \
	
LIB 		= -lpthread \
	-L/data/proj/cpp_examples/vnet -lVnet \
	-L/data/proj/cpp_examples/vlog -lVlog \
	-L/data/proj/cpp_examples/vutil -lVutil \
#
