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

void Sender::push(CPackage p){
	_queue.push(p);
}

int Sender::init(){
	return 0;
}

void Sender::process(){

	bool f = false;

	CPackage p;
	if(_queue.pop(p)){
		cout << SND_LOG("sender queue size (%i)\n", _queue.size());
		p._Send_Method(p._Stream, p._Message);
	}

	this_thread::sleep_for (std::chrono::seconds(1));
}



