/*
 * process.cpp
 *
 *  Created on: Jan 4, 2017
 *      Author: htqvinh
 */

#include <map>
#include "general.h"
#include "defines.h"
#include "Sender.h"

using namespace std;
extern Sender snd;
extern map<string, StreamBaseSptr > stream_map;

int process_packet_login (StreamBaseSptr sender, ByteBuffer& data);
int process_packet_chat_group (StreamBaseSptr sender, ByteBuffer& data);

int process_packet_to(CPackage &p){

	CPackage::Type type = p.type();

	std::function<int (StreamBaseSptr, ByteBuffer&)> f;
	switch(type){
	case CPackage::_LOGIN: { f = process_packet_login; break; }
	case CPackage::_CHATG: { f = process_packet_chat_group; break; }
	default: { f = NULL; break; }
	}

	if(f != NULL){
		f (p._Stream, p._Buffer);
	}

	return 0;
}

int process_packet_login (StreamBaseSptr sender, ByteBuffer& data){

	BYTE* dptr = data.dataPtr();

	unsigned length = 0;
	memcpy(&length, dptr + NUMBER_BYTES_OF_MSG_TYPE, NUMBER_BYTES_OF_MSG_LEN);



	return 0;
}

int process_packet_chat_group (StreamBaseSptr sender, ByteBuffer& data){

	BYTE* dptr = data.dataPtr() + NUMBER_BYTES_OF_MSG_TYPE;

	unsigned length = 0;
	memcpy(&length, dptr , NUMBER_BYTES_OF_MSG_LEN);
	dptr += NUMBER_BYTES_OF_MSG_LEN;

	if(length > 0){
		char content[length + 1];
		memcpy(content, dptr, length);
		content[length + 1] = '\0';
		cout << MAIN_LOG("Client IP[%s] PORT[%d] chat: %s\n",
							sender->Ip().c_str(), sender->Port(), content);
	}
	return 0;
}


