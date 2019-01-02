/*
 * Sender.cpp
 *
 *  Created on: Dec 27, 2016
 *      Author: htqvinh
 */

#include "Sender.h"
#include "defines.h"
#include "VHandler.h"

Sender::Sender(unsigned num_of_threads)
	: VHandler(num_of_threads){ }

Sender::~Sender() {}

void Sender::push(CPackage& p){
    std::unique_lock<std::mutex> lk(_mtx);
	_queue.push(p);
	_cv.notify_one();
}

int Sender::init(){
	return 0;
}

void Sender::process(){

	std::unique_lock<std::mutex> lk(_mtx);
	_cv.wait(lk, [this]() -> bool {
		if(_queue.isEmpty()){
			cout << "Sender is waiting for package coming...\n";
			return false;
		}
		return true;
	});

	CPackage p;
	_queue.pop(p);
	p._Send_Method(p._Stream, p._Buffer);

}



