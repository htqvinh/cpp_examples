/*
 * VHandler.cpp
 *
 *  Created on: Dec 30, 2016
 *      Author: htqvinh
 */

#include "VHandler.h"
#include <thread>
using namespace std;

VHandler::VHandler(unsigned num_of_thread)
	:_isActive(false), _Number_of_Threads(num_of_thread){}

VHandler::~VHandler() {}

void run(VHandler* ptr){
	if(!ptr) return;
	while(ptr->isActive()){
		ptr->process();
	}
}

void VHandler::active(bool f){
	if(_isActive == f){
		return;
	}
	_isActive = f;
	if(_isActive){
		for(unsigned i = 0; i < _Number_of_Threads; ++i){
			thread t(run, this);
			t.detach();
		}
	}
}

