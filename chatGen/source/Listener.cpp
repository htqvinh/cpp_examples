/*
 * Listener.cpp
 *
 *  Created on: Jan 12, 2017
 *      Author: htqvinh
 */

#include "Listener.h"

Listener::Listener(StreamBaseSptr stream_ptr, FunctionProcessMessage method, unsigned num_of_threads)
	:_StreamPtr(stream_ptr), _Process_Method(method), VHandler(num_of_threads){	}

Listener::~Listener(){ }

void Listener::process(){
	CMessage m;
	if(!recv_and_keep(_StreamPtr, m)){
		_Process_Method(m);
	}
}

