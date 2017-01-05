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
	_queue.lock();
	_queue.push(p);
	_queue.unlock();
}

void Sender::process(){

	bool f = false;
	CPackage p;

	_queue.lock();
	if(!_queue.isEmpty()){
		cout << SND_LOG("sender queue size (%i)\n", _queue.size());
		p = _queue.pop();
		f = true;
	}
	_queue.unlock();

	if(f == true){
		p._Method(p._Stream, p._Message);
	}

	this_thread::sleep_for (std::chrono::seconds(1));
}



