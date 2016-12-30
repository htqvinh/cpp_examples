/*
 * general.h
 *
 *  Created on: Dec 23, 2016
 *      Author: htqvinh
 */

#ifndef GENERAL_H_
#define GENERAL_H_

#include <stdio.h>
#include <functional>
#include "StreamBase.h"

enum MTYPE {
	MESS_A = 0,
	MESS_B,
	MESS_C,
	MESS_D,
	MESS_MAX
};

struct CMessage{

	MTYPE 		_Type;
	unsigned 	_Len;
	char*		_Data;

	CMessage(MTYPE type = MESS_MAX, unsigned len = 0, char* data = nullptr);
	~CMessage();
};

typedef std::function<int (StreamBaseSptr stream_ptr, CMessage m)> FunctionSend;

struct CPackage{
	StreamBaseSptr 		_Stream;
	CMessage 			_Message;
	FunctionSend 		_Method;

	CPackage(StreamBaseSptr stream, CMessage mess, FunctionSend method);
	~CPackage();
};

int send_and_close(StreamBaseSptr stream_ptr, CMessage m);
int send_and_keep(StreamBaseSptr stream_ptr, CMessage m);

#endif /* CHATGENERAL_H_ */
