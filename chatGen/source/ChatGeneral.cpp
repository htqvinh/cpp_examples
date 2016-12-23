/*
 * ChatGeneral.cpp
 *
 *  Created on: Dec 23, 2016
 *      Author: htqvinh
 */

#include "ChatGeneral.h"
#include "StreamBase.h"

int CMessage::sendTo(StreamBase* stream){

	if(!stream) return -1;

	unsigned size =
			1/*TYPE: 	1byte */ +
			1/*LEN: 	1byte */ + _Len;

	char buff[ size ];
	memcpy((void*)buff[0], (void*)_Type	, 1);
	memcpy((void*)buff[1], (void*)_Len	, 1);
	memcpy((void*)buff[2], (void*)_Data	, _Len);

	return stream->send(buff, size);
}


