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

int Processor::init(){
	return 0;
}

void Processor::process(){

//    std::unique_lock<std::mutex> lk(_Receiver._mtx);
//    _Receiver._cv.wait(lk, [this]() -> bool {
//		if(_Receiver._Pool.isEmpty()){
//			cout << "Receiver is waiting for package coming...\n";
//			return false;
//		}
//		return true;
//	});

//	CPackage p;
//	_Receiver._Pool.pop(p);
//	_Process_Method(p);

	CPackage p;
	_Receiver.waitToPopFromQueue(p);
	_Process_Method(p);

}
