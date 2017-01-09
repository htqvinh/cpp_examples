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

struct CMessage;
struct CPackage;

int send_and_close(StreamBaseSptr stream_ptr, CMessage m);
int send_and_keep(StreamBaseSptr stream_ptr, CMessage m);
int recv_and_close(StreamBaseSptr stream_ptr, CMessage& m);
int recv_and_keep(StreamBaseSptr stream_ptr, CMessage& m);

typedef std::function<int (const CPackage& p)> FunctionProc;
typedef std::function<int (StreamBaseSptr, CMessage )> FunctionSend;
typedef std::function<int (StreamBaseSptr, CMessage&)> FunctionRecv;

/**
 *
 */

struct CMessage{

	enum Type {
		MESS_A,
		MESS_B,
		MESS_C,
		MESS_D,
		MESS_MAX
	};

	Type 		_Type;
	string		_Data;

	CMessage(Type type = MESS_MAX, string data = "");
	~CMessage();
};

struct CPackage{

	StreamBaseSptr 		_Stream;
	CMessage 			_Message;
	FunctionSend 		_Send_Method;

	CPackage();
	CPackage(StreamBaseSptr stream, CMessage mess, FunctionSend method = send_and_close);
	~CPackage();
};

#endif /* CHATGENERAL_H_ */
