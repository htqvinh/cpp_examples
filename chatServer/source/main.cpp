/*
 * main.cpp
 *
 *  Created on: Dec 20, 2016
 *      Author: htqvinh
 */

#include <iostream>
#include "defines.h"
#include "AcceptorBase.h"

using namespace std;

int main (int argc, char** argv) {
	AcceptorTCP acc;
	if(acc.init(5001)){
		do{
			StreamBase* stream = acc.accept();
			cout << MAIN_LOG("has a connect from (%s)\n", stream->getIP().c_str());
		}while(true);
	}
	return 0;
}


