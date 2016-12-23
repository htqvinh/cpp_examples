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

	ConnectorTCP tcp;

	for(int i = 0; i < NUM_CONN; ++i){
		StreamBase* stream = tcp.connect("127.0.0.1", 5001);
		string hello = "Hello world!!!";
		CMessage mess = { MTYPE::MESS_A, hello.size(), hello.c_str()};
		mess.sendTo(stream);
	}

	cout << argv[0] << endl;
	return 0;
}


