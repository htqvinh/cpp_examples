/*
 * StreamBase.h
 *
 *  Created on: Dec 19, 2016
 *      Author: htqvinh
 */

#ifndef INCLUDE_STREAMBASE_H_
#define INCLUDE_STREAMBASE_H_

#include <iostream>
#include <memory>
#include <string.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include "VLog.h"
#include "defines.h"

using namespace std;

class StreamBase;
typedef shared_ptr<StreamBase> StreamBaseSptr;

class StreamBase {

	friend class ConnectorBase;
	friend class ConnectorTCP;
	friend class ConnectorUDP;

public:
	StreamBase(string ip, int port, int fd = -1);
	virtual ~StreamBase();
	virtual int send(char* buff, size_t len) = 0;
	virtual int recv(char* buff, size_t len) = 0;
	virtual int connect() = 0;
	virtual int close() = 0;

public:
	string 	Ip() 	{ return _Ip;  };
	int 	Port()  { return _Port;};
	int 	Fd()    { return _Fd;  };

protected:
	string  		_Ip;
	int     		_Port;
	int     		_Fd;
};

class StreamTCP
		: public StreamBase {
public:
	StreamTCP(string ip, int port, int fd = -1);
	virtual ~StreamTCP();
	int send(char* buff, size_t len);
	int recv(char* buff, size_t len);
	int connect();
	int close();
};

#endif /* INCLUDE_STREAMBASE_H_ */
