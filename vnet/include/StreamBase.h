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

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include "VLog.h"
#include "defines.h"

using namespace std;

class StreamBase {
public:
	StreamBase(int sockid, int port, string ip);
	virtual ~StreamBase();
	virtual int send(char* buff, size_t len) = 0;
	virtual int recv(char* buff, size_t len) = 0;

	int 	getSockId();
	int 	getPort();
	string 	getIP();

protected:
	int     	_sockId;
	int     	_peerPort;
	string  	_peerIP;
};

class StreamTCP
		: public StreamBase {
public:
	StreamTCP(int sockid, struct sockaddr_in* address);
	virtual ~StreamTCP();
	int send(char* buff, size_t len);
	int recv(char* buff, size_t len);
};

#endif /* INCLUDE_STREAMBASE_H_ */
