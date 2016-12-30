/*
 * Sender.cpp
 *
 *  Created on: Dec 27, 2016
 *      Author: htqvinh
 */

#include "Sender.h"
#include "defines.h"

Sender::Sender(unsigned num_of_threads)
	: VHandler(num_of_threads){ }

Sender::~Sender() {}

void Sender::push(CPackage p){
	_queue.push(p);
}

void Sender::process(){
	_queue.lock();
	cout << SND_LOG("sender queue size (%i)\n", _queue.size());
	if(!_queue.isEmpty()){
		CPackage p = _queue.pop();
		p._Method(p._Stream, p._Message);
	}
	_queue.unlock();
	this_thread::sleep_for (std::chrono::seconds(2));
}



