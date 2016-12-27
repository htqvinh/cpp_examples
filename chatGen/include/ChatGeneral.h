/*
 * ChatGeneral.h
 *
 *  Created on: Dec 23, 2016
 *      Author: htqvinh
 */

#ifndef CHATGENERAL_H_
#define CHATGENERAL_H_

#include <stdio.h>
#include "StreamBase.h"

enum MTYPE {
	MESS_A = 0,
	MESS_B,
	MESS_C,
	MESS_D,
};

struct CMessage{

	MTYPE 		_Type;
	unsigned 	_Len;
	char*		_Data;

	CMessage(MTYPE type, unsigned len, char* data);
	~CMessage();
};

int send_and_close(StreamBaseSptr stream_ptr, CMessage m);
int send_and_keep(StreamBaseSptr stream_ptr, CMessage m);

#endif /* CHATGENERAL_H_ */
