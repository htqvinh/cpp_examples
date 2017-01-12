/*
 * ChatGeneral.cpp
 *
 *  Created on: Dec 23, 2016
 *      Author: htqvinh
 */

#include <general.h>
#include "StreamBase.h"

CMessage::CMessage(Type type, string data)
	:_Type(type), _Data(data){ }

CMessage::~CMessage(){ }

CPackage::CPackage(){}

CPackage::CPackage(StreamBaseSptr stream, CMessage mess, FunctionSend method)
	:_Stream(stream), _Message(mess), _Send_Method(method){ }

CPackage::~CPackage(){ }

int send_message(const StreamBaseSptr& stream_ptr, const CMessage& m){

	if(-1 == stream_ptr->connect()) {
		return -1;
	}

	unsigned dlen = m._Data.size();
	unsigned char size =  dlen
			+ 1	/*TYPE: 	1byte */;

	char buff[ size ];
	buff[0] = m._Type	& 0xFF;
	memcpy((void*)(buff + 1), (void*)m._Data.c_str(), dlen);

	/* sent total size of packet */
	if(-1 == stream_ptr->send((char*)&size, sizeof(char)))
		return -1;

	/* sent data of packet */
	if(-1 == stream_ptr->send(buff, size)){
		return -1;
	}

	return 0;
}

int send_and_close(StreamBaseSptr stream_ptr, CMessage m){

	if(!stream_ptr) {
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

int recv_message(const StreamBaseSptr& stream_ptr, CMessage& m){

	unsigned char dlen;
	if(stream_ptr->recv((char*)&dlen, sizeof(char)) != 0){
		return -1;
	}

	/*
	 * Notes:
	 * - use string to store data, so length + 1
	 * - last byte to store '\0' at the end of data
	 */
	char buff[dlen + 1];
	memset(buff, 0, dlen + 1);
	if(stream_ptr->recv(buff, dlen) != 0){
		return -1;
	}

	m._Type = CMessage::Type(buff[0]);
	m._Data = string(buff + 1);

	return 0;
}

int recv_and_close(StreamBaseSptr stream_ptr, CMessage& m){

	if(!stream_ptr){
		return -1;
	}

	recv_message(stream_ptr, m);
	stream_ptr->close();

	return 0;
}

int recv_and_keep(StreamBaseSptr stream_ptr, CMessage& m){

	if(!stream_ptr){
		return -1;
	}

	recv_message(stream_ptr, m);

	return 0;
}



