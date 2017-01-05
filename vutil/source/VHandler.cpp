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

void VHandler::run(){
	while(_isActive){
		process();
	}
}

int VHandler::init(){
	return 0;
}

void VHandler::active(bool f){
	if(_isActive == f){
		return;
	}
	_isActive = f;
	if(_isActive){
		if(-1 == init()){
			_isActive = false;
			return;
		}
		for(unsigned i = 0; i < _Number_of_Threads; ++i){
			thread t(&VHandler::run, this);
			t.detach();
		}
	}
}

