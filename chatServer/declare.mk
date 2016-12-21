# editable
TARGET 		= ChatServer
SOURCEDIR 	= source
FLAGS 		= -g

INCLUDE 	= -I./include \
	-I/home/vinhhtq/cpp_examples/vnet/include \
	-I/home/vinhhtq/cpp_examples/vlog/include \
	
LIB 		= \
	-L/home/vinhhtq/cpp_examples/vnet -lVnet \
	-L/home/vinhhtq/cpp_examples/vlog -lVlog \
	-L/home/vinhhtq/cpp_examples/vutil -lVutil \
#
