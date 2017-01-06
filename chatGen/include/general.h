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
	MESS_A,
	MESS_B,
	MESS_C,
	MESS_D,
	MESS_MAX
};

struct CMessage{

	MTYPE 		_Type;
	string		_Data;

	CMessage(MTYPE type = MESS_MAX, string data = "");
	~CMessage();
};

typedef std::function<int (StreamBaseSptr stream_ptr, CMessage m)> FunctionSend;
int send_and_close(StreamBaseSptr stream_ptr, CMessage m);
int send_and_keep(StreamBaseSptr stream_ptr, CMessage m);
int recv_and_close(StreamBaseSptr stream_ptr, CMessage& m);
int recv_and_keep(StreamBaseSptr stream_ptr, CMessage& m);

struct CPackage{
	StreamBaseSptr 		_Stream;
	CMessage 			_Message;
	FunctionSend 		_Method;

	CPackage();
	CPackage(StreamBaseSptr stream, CMessage mess, FunctionSend method = send_and_close);
	~CPackage();
};

#endif /* CHATGENERAL_H_ */
