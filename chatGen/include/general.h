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
#include "VUtil.h"

struct CPackage;

int send_and_close(StreamBaseSptr, ByteBuffer&);
int send_and_keep(StreamBaseSptr, ByteBuffer&);
int recv_and_close(StreamBaseSptr stream_ptr, ByteBuffer&);
int recv_and_keep(StreamBaseSptr stream_ptr, ByteBuffer&);

typedef std::function<int (CPackage& )> 			FunctionProcessPackage;
typedef std::function<int (ByteBuffer& )> 			FunctionProcessMessage;
typedef std::function<int (StreamBaseSptr, ByteBuffer& )> 	FunctionSend;
typedef std::function<int (StreamBaseSptr, ByteBuffer& )> 	FunctionRecv;

#define NUMBER_BYTES_OF_MSG_TYPE 2
#define NUMBER_BYTES_OF_MSG_LEN 2

/**
 *
 */

struct CPackage{

	enum Type {
		_MIN = 0,
		_LOGIN,
		_LOGOUT,
		_CHATG,
		_MAX
	};

	StreamBaseSptr 		_Stream;
	ByteBuffer 			_Buffer;
	FunctionSend 		_Send_Method;

	CPackage() {

	}
	CPackage(StreamBaseSptr stream, ByteBuffer buffer, FunctionSend method = send_and_close)
		:_Stream(stream), _Buffer(buffer), _Send_Method(method) {

	}
	~CPackage() {

	}

	CPackage::Type type(){
		CPackage::Type t = CPackage::_MIN;
		if(_Buffer.length() >= NUMBER_BYTES_OF_MSG_TYPE){
			BYTE* dataptr = _Buffer.dataPtr();
			memcpy(&t, dataptr, NUMBER_BYTES_OF_MSG_TYPE);
		}
		return t;
	}

	unsigned length(){
		unsigned length = 0;
		if(_Buffer.length() >= (NUMBER_BYTES_OF_MSG_TYPE + NUMBER_BYTES_OF_MSG_LEN)){
			BYTE* dataptr = _Buffer.dataPtr() + NUMBER_BYTES_OF_MSG_TYPE;
			memcpy(&length, dataptr, NUMBER_BYTES_OF_MSG_LEN);
		}
		return length;
	}
};

#endif /* CHATGENERAL_H_ */
