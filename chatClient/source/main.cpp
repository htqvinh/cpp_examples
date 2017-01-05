/*
 * main.cpp
 *
 *  Created on: Dec 20, 2016
 *      Author: htqvinh
 */

#include <general.h>
#include <iostream>
#include "ConnectorBase.h"
#include "Sender.h"
using namespace std;

int main (int argc, char** argv) {

	CMessage message = { MESS_A, string("Hello world!!!")};
	StreamBaseSptr stream(new StreamTCP("127.0.0.1", 5001));

	Sender sender;
	sender.active(true);
	sender.push({ stream, message, send_and_close});
	sender.push({ stream, message, send_and_close});
	sender.push({ stream, message, send_and_close});
	sender.push({ stream, message, send_and_close});
	sender.push({ stream, message, send_and_close});
	sender.push({ stream, message, send_and_close});
	sender.push({ stream, message, send_and_close});

	while(1){ }

	return 0;
}
