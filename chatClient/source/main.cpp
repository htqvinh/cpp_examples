/*
 * main.cpp
 *
 *  Created on: Dec 20, 2016
 *      Author: htqvinh
 */

#include <iostream>
#include "ConnectorTCP.h"
using namespace std;

int main (int argc, char** argv) {
	ConnectorTCP tcp;
	tcp.connect("127.0.0.1", 5001);
	cout << argv[0] << endl;
	return 0;
}


