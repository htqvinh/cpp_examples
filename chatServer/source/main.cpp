/*
 * main.cpp
 *
 *  Created on: Dec 20, 2016
 *      Author: htqvinh
 */

#include <map>
#include <iostream>
#include "Sender.h"
#include "Processor.h"
#include "Receiver.h"

using namespace std;

extern int process_packet_to(CPackage &p);

int main (int argc, char** argv) {

	Sender snd;
	Receiver rec(AcceptorBaseSptr(new AcceptorTCP()), 5001);
	Processor pro(rec, process_packet_to);

	snd.active();
	rec.active();
	pro.active();

	while(1){}

	return 0;
}


