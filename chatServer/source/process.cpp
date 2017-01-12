/*
 * process.cpp
 *
 *  Created on: Jan 4, 2017
 *      Author: htqvinh
 */

#include "general.h"
#include "defines.h"

int process_packet_to(const CPackage &p){

	CMessage msg = p._Message;
	cout << MAIN_LOG("Message is %s\n", p._Message._Data.c_str());

	return 0;
}


