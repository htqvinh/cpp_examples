/*
 * ChatGeneral.h
 *
 *  Created on: Dec 23, 2016
 *      Author: htqvinh
 */

#ifndef CHATGENERAL_H_
#define CHATGENERAL_H_

#include <stdio.h>

class StreamBase;

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

	CMessage(MTYPE type = MESS_A, unsigned len = 0, char* data = NULL);
	~CMessage();
	int sendTo(StreamBase* stream);
	int recvFrom(StreamBase* stream);
};


#endif /* CHATGENERAL_H_ */
