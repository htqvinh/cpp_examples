/*
 * ChatGeneral.cpp
 *
 *  Created on: Dec 23, 2016
 *      Author: htqvinh
 */

#include <general.h>
#include "StreamBase.h"

CMessage::CMessage(MTYPE type, string data)
	:_Type(type), _Data(data){ }

CMessage::~CMessage(){ }

CPackage::CPackage(){}

CPackage::CPackage(StreamBaseSptr stream, CMessage mess, FunctionSend method)
	:_Stream(stream), _Message(mess), _Method(method){ }

CPackage::~CPackage(){ }

int send_message(const StreamBaseSptr& stream_ptr, const CMessage& m){

	unsigned dlen = m._Data.size();
	unsigned size =
				1/*TYPE: 	1byte */ +
				1/*LEN: 	1byte */ + dlen;

	char buff[ size ];
	buff[0] = m._Type	& 0xFF;
	buff[1] = dlen 		& 0xFF;
	memcpy((void*)(buff + 2), (void*)m._Data.c_str(), dlen);

	if(-1 == stream_ptr->send(buff, size))
		return -1;

	return 0;
}

int send_and_close(StreamBaseSptr stream_ptr, CMessage m){

	if(!stream_ptr) {
		return -1;
	}
	if(-1 == stream_ptr->connect()) {
		return -1;
	}
	send_message(stream_ptr, m);
	stream_ptr->close();
	return 0;
}

int send_and_keep(StreamBaseSptr stream_ptr, CMessage m){

	if(!stream_ptr) {
		return -1;
	}
	send_message(stream_ptr, m);
	return 0;
}

int recv_and_close(StreamBaseSptr stream_ptr, CMessage& m){

	if(!stream_ptr){
		return -1;
	}

	MTYPE type;
	if(stream_ptr->recv((char*)&type, 1) != 0){
		return -1;
	}

	unsigned char dlen;
	if(stream_ptr->recv((char*)&dlen, 1) != 0){
		return -1;
	}

	char buff[dlen];
	if(stream_ptr->recv(buff, dlen) != 0){
		return -1;
	}

	m = {type, string(buff)};

	stream_ptr->close();
	return 0;
}



