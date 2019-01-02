/*
 * main.cpp
 *
 *  Created on: Dec 20, 2016
 *      Author: htqvinh
 */

#include <iostream>
#include "general.h"
#include "ConnectorBase.h"
#include "Sender.h"
using namespace std;


void compose_buff_to_send_(ByteBuffer& buff,
		CPackage::Type type, unsigned length, const void* data)
{
	buff.append(&type, NUMBER_BYTES_OF_MSG_TYPE);
	buff.append(&length, NUMBER_BYTES_OF_MSG_LEN);
	buff.append(data, length);
}

int main (int argc, char** argv) {

	Sender sender;
	sender.active(true);

	const char* str = "Hello world!!!";

	ByteBuffer buff;
	compose_buff_to_send_(buff, CPackage::_CHATG, strlen(str), str);

//	StreamBaseSptr stream(new StreamUDP("127.0.0.1", 5001));
	StreamBaseSptr stream(new StreamTCP("127.0.0.1", 5001));

	CPackage p (stream, buff, send_and_keep);

	sender.push(p);
	sender.push(p);
	sender.push(p);

	while(1){ }

	return 0;
}
