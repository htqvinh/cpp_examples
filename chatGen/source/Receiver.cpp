/*
 * Receiver.cpp
 *
 *  Created on: Dec 27, 2016
 *      Author: htqvinh
 */

#include "Receiver.h"

Receiver::Receiver(
		AcceptorBaseSptr acceptor, unsigned port,
		std::function<int (StreamBaseSptr, CMessage& )> recv_method,
		unsigned num_of_threads)
:
		_Acceptor(acceptor), _Port(port),
		_Recv_Method(recv_method),
		VHandler(num_of_threads){ }

Receiver::~Receiver() { }

int Receiver::init(){
	if(nullptr == _Acceptor)
		return -1;
	if(-1 == _Acceptor->init(_Port))
		return -1;
	return 0;
}

void Receiver::process(){

	StreamBaseSptr stream = _Acceptor->accept();
	if(nullptr == stream)
		return;
	cout << REC_LOG("One connection from (%s)\n", stream->Ip().c_str());

	CMessage m;
	if(!_Recv_Method(stream, m)){
		_Pool.lock();
		_Pool.push({stream, m});
		_Pool.unlock();
	}
}

