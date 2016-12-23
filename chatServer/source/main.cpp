/*
 * main.cpp
 *
 *  Created on: Dec 20, 2016
 *      Author: htqvinh
 */

#include <iostream>
#include <thread>
#include "defines.h"
#include "AcceptorBase.h"

using namespace std;

void listen_func(AcceptorBase* acc){
	while(acc){
		StreamBase* stream = acc->accept();
		cout << MAIN_LOG("has a connect from (%s)\n", stream->getIP().c_str());
	}
}

int main (int argc, char** argv) {

	AcceptorTCP acc;
	if(acc.init(5001)){
		std::thread t(listen_func, &acc);
		t.join();
	}

	return 0;
}


