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

struct StreamInfo{
	string  		_Ip;
	int     		_Port;
	int     		_Fd;


	StreamInfo() = delete;
	StreamInfo(string ip, int port, int fd = -1)
		:_Ip(ip), _Port(port), _Fd(fd)
	{
	}


	bool operator < (const StreamInfo& info) const {
		if(!(_Port < info._Port))
			return false;
		if(_Ip.compare(info._Ip) == 0)
			return false;
		return true;
	}
};

class StreamBase {

	friend class ConnectorBase;
	friend class ConnectorTCP;
	friend class ConnectorUDP;

public:
	StreamBase(string ip, int port, int fd = -1) :_Info(ip, port, fd){}
	virtual ~StreamBase() { }
	virtual int send(void* buff, size_t len) = 0;
	virtual int recv(void* buff, size_t len) = 0;
	virtual int connect() = 0;
	virtual int close() = 0;

public:
	string 	Ip() 		{ return _Info._Ip;  };
	int 	Port()  	{ return _Info._Port;};
	int 	Fd()    	{ return _Info._Fd;  };
	StreamInfo Info() 	{ return _Info; };

protected:
	StreamInfo _Info;
};

class StreamTCP
		: public StreamBase {

public:
	StreamTCP(string ip, int port, int fd = -1): StreamBase(ip, port, fd){}
	virtual ~StreamTCP() { }
	int send(void* buff, size_t len);
	int recv(void* buff, size_t len);
	int connect();
	int close();
};

class StreamUDP
		: public StreamBase {

public:
	StreamUDP(string ip, int port, int fd = -1): StreamBase(ip, port, fd){ }
	virtual ~StreamUDP() { }
	int send(void* buff, size_t len);
	int recv(void* buff, size_t len);
	int connect();
	int close();
};

#endif /* INCLUDE_STREAMBASE_H_ */
