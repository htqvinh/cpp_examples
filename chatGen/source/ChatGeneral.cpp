/*
 * ChatGeneral.cpp
 *
 *  Created on: Dec 23, 2016
 *      Author: htqvinh
 */

#include "ChatGeneral.h"
#include "StreamBase.h"

CMessage::CMessage(MTYPE type, unsigned len, char* data)
	:_Type(type), _Len(len), _Data(data)
{

}

CMessage::~CMessage(){

}

int send_m(const StreamBaseSptr& stream_ptr, const CMessage& m){

	unsigned size =
				1/*TYPE: 	1byte */ +
				1/*LEN: 	1byte */ + m._Len;

	char buff[ size ];
	buff[0] = m._Type	& 0xFF;
	buff[1] = m._Len 	& 0xFF;
	memcpy((void*)(buff + 2), (void*)m._Data, m._Len);

	if( -1 == stream_ptr->send(buff, size))
		return -1;

	return 0;
}

int send_and_close(StreamBaseSptr stream_ptr, CMessage m){
	if(!stream_ptr) return -1;
	if( -1 == stream_ptr->connect()) return -1;

	send_m(stream_ptr, m);

	stream_ptr->close();
	return 0;
}

int send_and_keep(StreamBaseSptr stream_ptr, CMessage m){
	if(!stream_ptr) return -1;

	send_m(stream_ptr, m);

	stream_ptr->close();
	return 0;
}



