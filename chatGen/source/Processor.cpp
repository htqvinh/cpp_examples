/*
 * Processor.cpp
 *
 *  Created on: Jan 3, 2017
 *      Author: htqvinh
 */

#include "Processor.h"
#include "Receiver.h"

Processor::Processor(Receiver &recv, FunctionProcessPackage method, unsigned num_of_threads)
	:_Receiver(recv), _Process_Method(method), VHandler(num_of_threads){ }

Processor::~Processor() {
}

void Processor::process(){

	bool f = false;
	CPackage p;

	_Receiver._Pool.lock();
	if(!_Receiver._Pool.isEmpty()){
		f = true;
		p = _Receiver._Pool.pop();
	}
	_Receiver._Pool.unlock();

	if(f == true){
		_Process_Method(p);
	}
}
