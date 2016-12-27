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

int CMessage::sendTo(StreamBase* stream){

	if(!stream) return -1;

	unsigned size =
			1/*TYPE: 	1byte */ +
			1/*LEN: 	1byte */ + _Len;

	char buff[ size ];
	buff[0] = _Type & 0xFF;
	buff[1] = _Len 	& 0xFF;
	memcpy((void*)(buff + 2), (void*)_Data, (size_t)_Len);
	return stream->send(buff, size);
}


