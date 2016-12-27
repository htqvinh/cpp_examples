/*
 * main.cpp
 *
 *  Created on: Dec 20, 2016
 *      Author: htqvinh
 */

#include <iostream>
#include "ChatGeneral.h"
#include "ConnectorBase.h"
using namespace std;

#define NUM_CONN 1000

int main (int argc, char** argv) {

	StreamBaseSptr stream(new StreamTCP("127.0.0.1", 5001));

	ConnectorTCP tcp;
	if(tcp.connect(stream) == -1){
		return -1;
	}

	string hello = "Hello world!!!";
	CMessage mess = { MESS_A, (unsigned)hello.size(), (char*)hello.c_str()};
	mess.sendTo(stream.get());

	cout << argv[0] << endl;
	return 0;
}


