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

	Sender sender;
	sender.active(true);

	string hello = "Hello world!!!";
	CMessage mess = { MESS_A, (unsigned)hello.size(), (char*)hello.c_str()};
	StreamBaseSptr stream(new StreamTCP("127.0.0.1", 5001));

	sender.push({ stream, mess, send_and_close});
	sender.push({ stream, mess, send_and_close});
	sender.push({ stream, mess, send_and_close});

	this_thread::sleep_for (std::chrono::seconds(10));

	return 0;
}
