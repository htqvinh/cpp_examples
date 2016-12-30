/*
 * Sender.cpp
 *
 *  Created on: Dec 27, 2016
 *      Author: htqvinh
 */

#include "Sender.h"
#include "defines.h"

Sender::Sender()
	:_isActive(false)
{
}

Sender::~Sender() {}

void Sender::push(CPackage p){
	_queue.push(p);
}

void Sender::active(bool f){

	if(_isActive == f) {
		return;
	}
	_isActive = f;
	if(_isActive) {
		thread t(&Sender::process, this);
		t.detach();
	}
}

void Sender::process(){
	while(_isActive){
		_queue.lock();
		cout << SND_LOG("sender queue size (%i)\n", _queue.size());
		if(!_queue.isEmpty()){
			CPackage p = _queue.pop();
			p._Method(p._Stream, p._Message);
		}
		_queue.unlock();
		this_thread::sleep_for (std::chrono::seconds(2));
	}
}



