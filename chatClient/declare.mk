# editable
TARGET 		= ChatClient
SOURCEDIR 	= source
DEBUG 		= -m64

INCLUDE 	= -I./include \
	-I/data/proj/cpp_examples/vnet/include \
	-I/data/proj/cpp_examples/vlog/include \
	
LIB 		= \
	-L/data/proj/cpp_examples/vnet -lVnet \
	-L/data/proj/cpp_examples/vlog -lVlog \
	-L/data/proj/cpp_examples/vutil -lVutil \
#
