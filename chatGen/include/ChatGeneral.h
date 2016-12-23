/*
 * ChatGeneral.h
 *
 *  Created on: Dec 23, 2016
 *      Author: htqvinh
 */

#ifndef CHATGENERAL_H_
#define CHATGENERAL_H_

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

	int sendTo(StreamBase* stream);
	int recvFrom(StreamBase* stream);
};


#endif /* CHATGENERAL_H_ */
