/*
 * StreamBase.h
 *
 *  Created on: Dec 19, 2016
 *      Author: htqvinh
 */

#ifndef INCLUDE_STREAMBASE_H_
#define INCLUDE_STREAMBASE_H_

#include <iostream>
#include <string.h>
//#include <stdlib.h>
//#include <unistd.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "VLog.h"

using namespace std;

class StreamBase {
public:
	StreamBase();
	virtual ~StreamBase();
	virtual int send(char* buff, size_t len) = 0;
	virtual int recv(char* buff, size_t len) = 0;

protected:
	int     	_sockId;
	int     	_peerPort;
	string  	_peerIP;
};

#endif /* INCLUDE_STREAMBASE_H_ */
