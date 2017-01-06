/*
 * main.cpp
 *
 *  Created on: Dec 20, 2016
 *      Author: htqvinh
 */

#include <iostream>
#include "Processor.h"
#include "Receiver.h"

using namespace std;

extern int process_packet_to(const CPackage &p);

int main (int argc, char** argv) {

//	Receiver rec(AcceptorBaseSptr(new AcceptorTCP()), 5001, recv_and_close);
	Receiver rec(AcceptorBaseSptr(new AcceptorUDP()), 5002, recv_and_keep);
	Processor pro(rec, process_packet_to);
	rec.active();
	pro.active();

	while(1){ }
	return 0;
}


